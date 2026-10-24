# organize.ps1 - file AC'd Codeforces solutions into old\YYYY\MM\DD\ by AC time
#
#   * AC time = creationTimeSeconds of the FIRST Accepted submission (CF API)
#   * each moved .cpp also gets its cph metadata fixed: the .prob file is
#     renamed to md5(new path) and its "srcPath" field is rewritten, so the
#     Competitive Programming Helper keeps the sample tests attached.
#
# Usage:
#   .\organize.ps1                 # dry run, prints what would happen
#   .\organize.ps1 -Apply          # do it
#   .\organize.ps1 -Apply -Unaccept   # also move non-AC'd files to unaccept\
#
# Notes:
#   * contest files (..\OI\contests\CF\<contestId>\) are NOT touched here:
#     they stay grouped per contest.  Their "// Time" line is the contest
#     start, so solving time must be measured from the contest start.

param(
    [switch]$Apply,
    [switch]$Unaccept,
    [string]$Root = 'D:\code\OI\codeforces'
)

$ErrorActionPreference = 'Stop'
$statusPath = Join-Path $PSScriptRoot 'cache\status.json'
$oldDir = Join-Path $Root 'old'
$unacceptDir = Join-Path $Root 'unaccept'

function Update-Status {
    $fresh = (Test-Path $statusPath) -and ((Get-Date) - (Get-Item $statusPath).LastWriteTime).TotalMinutes -lt 10
    if ($fresh) { return }
    curl.exe -s -m 90 -o $statusPath 'https://codeforces.com/api/user.status?handle=yuxinhao&from=1&count=10000' | Out-Null
    if (((Get-Content $statusPath -Raw | ConvertFrom-Json).status) -ne 'OK') {
        throw "failed to refresh $statusPath"
    }
}

function Get-PathHash([string]$Path) {
    $md5 = [System.Security.Cryptography.MD5]::Create()
    try { $bytes = $md5.ComputeHash([Text.Encoding]::UTF8.GetBytes($Path)) }
    finally { $md5.Dispose() }
    ($bytes | ForEach-Object { $_.ToString('x2') }) -join ''
}

# cph stores the path with a lower-case drive letter, e.g. d:\code\OI\codeforces\4C.cpp
function Get-CphPath([string]$Path) {
    if ($Path.Length -lt 2) { return $Path }
    $Path.Substring(0, 1).ToLower() + $Path.Substring(1)
}

# cph keeps one state file per source file, next to it:
#   <dir>\.cph\.<name>_<md5(path)>.prob   (UTF-8, no BOM - it uses JSON.parse)
function Get-ProbPath([string]$File) {
    Join-Path (Join-Path (Split-Path $File -Parent) '.cph') `
              ('.{0}_{1}.prob' -f (Split-Path $File -Leaf), (Get-PathHash (Get-CphPath $File)))
}

function Move-Cph($From, $To) {
    $probFrom = Get-ProbPath $From
    $probTo = Get-ProbPath $To

    if ((Test-Path $probTo) -and -not (Test-Path $probFrom)) { return 'cph ok' }
    if (-not (Test-Path $probFrom)) { return 'cph MISSING' }

    $json = [IO.File]::ReadAllText($probFrom, [Text.Encoding]::UTF8) | ConvertFrom-Json
    $json.srcPath = Get-CphPath $To
    $cphDir = Split-Path $probTo -Parent
    if (-not (Test-Path $cphDir)) { New-Item -ItemType Directory -Force -Path $cphDir | Out-Null }
    # cph parses its state with JSON.parse: UTF-8 without BOM
    [IO.File]::WriteAllText($probTo, ($json | ConvertTo-Json -Depth 20 -Compress),
        (New-Object System.Text.UTF8Encoding($false)))
    if ($probFrom -ne $probTo) {
        Remove-Item $probFrom -Force
        # drop a .cph folder that just became empty
        $fromDir = Split-Path $probFrom -Parent
        if ((Get-ChildItem $fromDir -Force | Measure-Object).Count -eq 0) { Remove-Item $fromDir -Force }
    }
    return 'cph moved'
}

Update-Status
$status = (Get-Content $statusPath -Raw | ConvertFrom-Json).result

$acMap = @{}
foreach ($s in ($status | Sort-Object creationTimeSeconds)) {
    $id = "$($s.problem.contestId)$($s.problem.index)"
    if ($s.verdict -eq 'OK' -and -not $acMap.ContainsKey($id)) {
        $acMap[$id] = [DateTimeOffset]::FromUnixTimeSeconds($s.creationTimeSeconds).ToOffset([TimeSpan]::FromHours(8))
    }
}

$plan = @()
$files = Get-ChildItem $Root -Recurse -File -Filter *.cpp | Where-Object {
    $_.FullName -notlike "*$([IO.Path]::DirectorySeparatorChar).cph$([IO.Path]::DirectorySeparatorChar)*" -and
    $_.FullName -notlike "*$([IO.Path]::DirectorySeparatorChar)unaccept$([IO.Path]::DirectorySeparatorChar)*" -and
    $_.FullName -notlike '*\stress_out\*' -and
    $_.FullName -notmatch '\\old\\\d{4}\\\d{2}\\\d{2}\\'
}

foreach ($f in $files) {
    $id = $null
    if ($f.BaseName -match '^(\d+)([A-Z]\d*)$') { $id = $Matches[1] + $Matches[2] }

    if ($id -and $acMap.ContainsKey($id)) {
        $ac = $acMap[$id]
        $target = Join-Path $oldDir ('{0}\{1}\{2}' -f $ac.ToString('yyyy'), $ac.ToString('MM'), $ac.ToString('dd'))
        $plan += [pscustomobject]@{
            File = $f.Name; Id = $id; Ac = $ac.ToString('yyyy-MM-dd HH:mm')
            Action = 'move'; Dest = Join-Path $target $f.Name; Src = $f.FullName
        }
    }
    elseif ($Unaccept) {
        $plan += [pscustomobject]@{
            File = $f.Name; Id = $id; Ac = '-'
            Action = 'unaccept'; Dest = Join-Path $unacceptDir $f.Name; Src = $f.FullName
        }
    }
    else {
        $plan += [pscustomobject]@{
            File = $f.Name; Id = $id; Ac = 'no AC'
            Action = 'skip'; Dest = ''; Src = $f.FullName
        }
    }
}

if (-not $plan) { 'nothing to do'; return }

foreach ($p in ($plan | Sort-Object Action, Ac)) {
    $tag = switch ($p.Action) { 'move' { 'MOVE' } 'unaccept' { 'UNAC' } default { 'skip' } }
    "{0} {1,-12} {2,-16} -> {3}" -f $tag, $p.File, $p.Ac, $(if ($p.Dest) { $p.Dest.Substring($Root.Length + 1) } else { '(stays)' })
}

if (-not $Apply) { ''; 'dry run - pass -Apply to execute'; return }

$moved = 0
foreach ($p in $plan) {
    if ($p.Action -eq 'skip') { continue }
    if (-not (Test-Path $p.Src)) { "gone: $($p.Src)"; continue }
    if ((Test-Path $p.Dest) -and ((Get-FileHash $p.Dest).Hash -ne (Get-FileHash $p.Src).Hash)) {
        "CONFLICT, both exist and differ: $($p.Dest)"; continue
    }
    New-Item -ItemType Directory -Force -Path (Split-Path $p.Dest) | Out-Null
    Move-Item -LiteralPath $p.Src -Destination $p.Dest -Force
    $cph = Move-Cph $p.Src $p.Dest
    $moved++
}

''
"moved $moved file(s)"
