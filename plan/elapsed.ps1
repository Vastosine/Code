# elapsed.ps1 - compute time spent per problem
#   start = the "// Time : yyyy-MM-dd HH:mm:ss" line (line 2 of the file)
#   end   = creation time of the FIRST Accepted submission (Codeforces API)
#
# Usage:
#   .\elapsed.ps1 ..\..\OI\codeforces\825D.cpp
#   .\elapsed.ps1 ..\..\OI\codeforces\*.cpp

param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Files
)

$ErrorActionPreference = 'Stop'
$statusPath = Join-Path $PSScriptRoot 'cache\status.json'

function Update-Status {
    $fresh = (Test-Path $statusPath) -and ((Get-Date) - (Get-Item $statusPath).LastWriteTime).TotalMinutes -lt 10
    if ($fresh) { return }
    curl.exe -s -m 60 -o $statusPath "https://codeforces.com/api/user.status?handle=yuxinhao&from=1&count=500" | Out-Null
}

Update-Status
$status = (Get-Content $statusPath -Raw | ConvertFrom-Json).result

foreach ($f in $Files) {
    if (-not (Test-Path $f)) { "missing: $f"; continue }
    $path = (Resolve-Path $f).Path
    $lines = Get-Content $path -TotalCount 2
    $head = $lines[0]
    $timeLine = $lines[1]

    $m = [regex]::Match($head, '(?:problem|contest)/(\d+)/(?:problem/)?([A-Za-z0-9]+)')
    if (-not $m.Success) { "$([IO.Path]::GetFileName($path)): cannot parse problem id from line 1"; continue }
    $cid = [int]$m.Groups[1].Value
    $idx = $m.Groups[2].Value

    $t = [regex]::Match($timeLine, 'Time\s*:\s*(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})')
    if (-not $t.Success) { "$([IO.Path]::GetFileName($path)): cannot parse start time from line 2"; continue }
    $start = [datetime]::ParseExact($t.Groups[1].Value, 'yyyy-MM-dd HH:mm:ss', $null)

    $all = $status | Where-Object {
        $_.problem.contestId -eq $cid -and $_.problem.index -eq $idx
    } | Sort-Object creationTimeSeconds

    $name = "$cid$idx"
    $ac = $all | Where-Object { $_.verdict -eq 'OK' } | Select-Object -First 1
    if (-not $ac) { "{0,-10} start {1:HH:mm}  no AC yet" -f $name, $start; continue }

    $endLocal = [DateTimeOffset]::FromUnixTimeSeconds($ac.creationTimeSeconds).ToOffset([TimeSpan]::FromHours(8)).DateTime
    $subsBefore = @($all | Where-Object { $_.creationTimeSeconds -lt $ac.creationTimeSeconds }).Count
    $mins = [math]::Round(($endLocal - $start).TotalMinutes)
    "{0,-10} start {1:HH:mm:ss}  AC {2:HH:mm:ss}  elapsed {3,3} min  subs before AC: {4}" -f `
        $name, $start, $endLocal, $mins, $subsBefore
}
