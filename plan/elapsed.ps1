# elapsed.ps1 - time spent per problem
#
#   normal practice file (OI\codeforces\...\):
#       start = the "// Time : yyyy-MM-dd HH:mm:ss" line (line 2 of the file)
#       end   = creation time of the FIRST Accepted submission (Codeforces API)
#
#   contest file (OI\contests\CF\<contestId>\):
#       every problem in the set is created at the same moment, so that
#       "// Time" is the contest start, not the moment a problem was started.
#       -> time is measured from the contest start, and the per-problem cost
#          is shown as the difference to the previous AC in the same contest.
#
# Usage:
#   .\elapsed.ps1 ..\..\OI\codeforces\old\2026\10\23\825D.cpp
#   .\elapsed.ps1 ..\..\OI\contests\CF\2261\2261C.cpp

param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Files
)

$ErrorActionPreference = 'Stop'
$statusPath = Join-Path $PSScriptRoot 'cache\status.json'
$cacheDir = Split-Path $statusPath -Parent
if (-not (Test-Path $cacheDir)) { New-Item -ItemType Directory -Force -Path $cacheDir | Out-Null }

function Test-StatusFile([string]$Path) {
    if (-not (Test-Path $Path)) { return $false }
    try { return ((Get-Content $Path -Raw | ConvertFrom-Json).status -eq 'OK') } catch { return $false }
}

# 2026-11-03 fix: curl -m 90 once truncated the response at 1913 bytes and left a
# half-written cache file behind. Now: download to .tmp, validate the JSON, then
# move into place; retry 3x. A partial file can never become the cache.
function Update-Status {
    if ((Test-Path $statusPath) -and
        ((Get-Date) - (Get-Item $statusPath).LastWriteTime).TotalMinutes -lt 10 -and
        (Test-StatusFile $statusPath)) { return }
    $tmp = "$statusPath.tmp"
    for ($attempt = 1; $attempt -le 3; $attempt++) {
        if (Test-Path $tmp) { Remove-Item $tmp -Force }
        curl.exe -s -m 300 -o $tmp 'https://codeforces.com/api/user.status?handle=yuxinhao&from=1&count=10000' | Out-Null
        if ((Test-StatusFile $tmp) -and (Get-Item $tmp).Length -gt 10000) {
            Move-Item $tmp $statusPath -Force
            return
        }
        if (Test-Path $tmp) { Remove-Item $tmp -Force }
        Write-Host "  status download attempt $attempt failed (truncated or invalid), retrying..."
        Start-Sleep -Seconds 3
    }
    throw "failed to refresh $statusPath after 3 attempts"
}

function Get-Info([string]$Path) {
    $lines = Get-Content $Path -TotalCount 2
    $m = [regex]::Match($lines[0], '(?:problem|contest)/(\d+)/(?:problem/)?([A-Za-z0-9]+)')
    $t = [regex]::Match($lines[1], 'Time\s*:\s*(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})')
    if (-not $m.Success -or -not $t.Success) { return $null }
    [pscustomobject]@{
        Path  = $Path
        Name  = [IO.Path]::GetFileNameWithoutExtension($Path)
        Cid   = [int]$m.Groups[1].Value
        Idx   = $m.Groups[2].Value
        Start = [datetime]::ParseExact($t.Groups[1].Value, 'yyyy-MM-dd HH:mm:ss', $null)
        Contest = $Path -match '\\contests\\CF\\\d+\\'
    }
}

Update-Status
$status = (Get-Content $statusPath -Raw | ConvertFrom-Json).result

function Get-Subs($Info) {
    $status | Where-Object { $_.problem.contestId -eq $Info.Cid -and $_.problem.index -eq $Info.Idx } |
        Sort-Object creationTimeSeconds
}

function Get-Ac($Info) { Get-Subs $Info | Where-Object verdict -eq 'OK' | Select-Object -First 1 }

$infos = @()
foreach ($f in $Files) {
    if (-not (Test-Path $f)) { "missing: $f"; continue }
    $p = (Resolve-Path $f).Path
    $i = Get-Info $p
    if (-not $i) { "$([IO.Path]::GetFileName($p)): cannot parse header"; continue }
    $infos += $i
}

# a contest set is judged as a whole: expand to every source file of that contest
$expanded = @{}
$groups = @()
foreach ($i in $infos) {
    if (-not $i.Contest) { $groups += , @($i); continue }
    $dir = Split-Path $i.Path -Parent
    if ($expanded.ContainsKey($dir)) { continue }
    $set = @()
    foreach ($f in (Get-ChildItem $dir -File -Filter *.cpp | Sort-Object Name)) {
        $j = Get-Info $f.FullName
        if ($j -and (Get-Ac $j)) { $set += $j }
    }
    if (-not $set) { continue }
    $expanded[$dir] = $true
    $groups += , @($set | Sort-Object { (Get-Ac $_).creationTimeSeconds })
}

foreach ($g in $groups) {
    $prev = $null
    foreach ($i in $g) {
        $ac = Get-Ac $i
        if (-not $ac) { "{0,-10} no AC yet" -f $i.Name; continue }
        $subs = Get-Subs $i
        $subsBefore = @($subs | Where-Object { $_.creationTimeSeconds -lt $ac.creationTimeSeconds }).Count
        $end = [DateTimeOffset]::FromUnixTimeSeconds($ac.creationTimeSeconds).ToOffset([TimeSpan]::FromHours(8)).DateTime
        $since = [math]::Round(($end - $i.Start).TotalMinutes)

        if (-not $i.Contest) {
            "{0,-10} start {1:HH:mm:ss}  AC {2:HH:mm:ss}  elapsed {3,4} min  subs {4}" -f `
                $i.Name, $i.Start, $end, $since, $subsBefore
        }
        else {
            $delta = if ($prev) { [math]::Round(($end - $prev).TotalMinutes) } else { $since }
            "{0,-10} contest {1:HH:mm:ss}  AC {2:HH:mm:ss}  +{3,4} min  delta {4,4} min  subs {5}" -f `
                $i.Name, $i.Start, $end, $since, $delta, $subsBefore
            $prev = $end
        }
    }
}
