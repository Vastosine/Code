# organize_luogu.ps1 - file Luogu solutions into old\YYYY\MM\DD\
#
# Differences from organize.ps1 (the CF version):
#
#   * CF uses the first-AC time from the CF API. The Luogu record API needs a
#     session (all cookie attempts returned 401), so AC time is NOT available.
#   * Date source, in priority order:
#       1. the "// Time : YYYY-MM-DD" header (CPH writes it when the file is
#          created = when the problem was started)          -> exact
#       2. the file's mtime                                  -> approximate
#       3. old\unknown\                                      -> mtime is an artifact
#   * Artifact detection: a bulk copy/restore stamps several files with the
#     exact same second. Rule: >=3 headerless files sharing the same
#     yyyy-MM-dd HH:mm:ss -> that timestamp is an artifact, park them in
#     old\unknown\ instead of inventing a date.
#     (Real sessions spread over seconds; e.g. 2026-09-01 17:31 has :20 :21
#      :24 :25 -> legitimate. 2026-02-18 11:18 has :20 x11, :21 x51 -> artifact.)
#
# Same as the CF version:
#   * .cph state files are migrated too: renamed to md5(new path) and srcPath
#     rewritten, otherwise Competitive Programming Helper loses the samples.
#   * If the destination exists with different content -> skip and report
#     CONFLICT, never overwrite.
#
# Usage:
#   .\organize_luogu.ps1                   # dry run
#   .\organize_luogu.ps1 -Apply            # do it
#   .\organize_luogu.ps1 -Apply -Unaccept  # also move 0-byte stubs to unaccept\
#
# Idempotent: only the direct children of $Root are scanned (not recursive),
# so anything already under old\ is never moved twice.

param(
    [switch]$Apply,
    [switch]$Unaccept,
    [int]$ArtifactThreshold = 3,
    [string]$Root = 'D:\code\OI\luogu\problems'
)

$ErrorActionPreference = 'Stop'
$oldDir = Join-Path $Root 'old'
$unacceptDir = Join-Path $Root 'unaccept'

function Get-PathHash([string]$Path) {
    $md5 = [System.Security.Cryptography.MD5]::Create()
    try { $bytes = $md5.ComputeHash([Text.Encoding]::UTF8.GetBytes($Path)) }
    finally { $md5.Dispose() }
    ($bytes | ForEach-Object { $_.ToString('x2') }) -join ''
}

# cph stores the path with a lower-case drive letter
function Get-CphPath([string]$Path) {
    if ($Path.Length -lt 2) { return $Path }
    $Path.Substring(0, 1).ToLower() + $Path.Substring(1)
}

function Get-ProbPath([string]$File) {
    Join-Path (Join-Path (Split-Path $File -Parent) '.cph') `
              ('.{0}_{1}.prob' -f (Split-Path $File -Leaf), (Get-PathHash (Get-CphPath $File)))
}

function Move-Cph($From, $To) {
    $probFrom = Get-ProbPath $From
    $probTo = Get-ProbPath $To

    if ((Test-Path $probTo) -and -not (Test-Path $probFrom)) { return 'cph ok' }
    if (-not (Test-Path $probFrom)) { return 'cph none' }

    $json = [IO.File]::ReadAllText($probFrom, [Text.Encoding]::UTF8) | ConvertFrom-Json
    $json.srcPath = Get-CphPath $To
    $cphDir = Split-Path $probTo -Parent
    if (-not (Test-Path $cphDir)) { New-Item -ItemType Directory -Force -Path $cphDir | Out-Null }
    # cph parses with JSON.parse: UTF-8 without BOM
    [IO.File]::WriteAllText($probTo, ($json | ConvertTo-Json -Depth 20 -Compress),
        (New-Object System.Text.UTF8Encoding($false)))
    if ($probFrom -ne $probTo) {
        Remove-Item $probFrom -Force
        $fromDir = Split-Path $probFrom -Parent
        if ((Get-ChildItem $fromDir -Force | Measure-Object).Count -eq 0) { Remove-Item $fromDir -Force }
    }
    return 'cph moved'
}

function Test-HasTimeHeader($Path) {
    $head = Get-Content $Path -TotalCount 4 -Encoding UTF8 -ErrorAction SilentlyContinue
    return [bool]($head -match '^//\s*Time\s*:')
}

function Get-HeaderDate($Path) {
    $head = Get-Content $Path -TotalCount 4 -Encoding UTF8 -ErrorAction SilentlyContinue
    foreach ($line in $head) {
        if ($line -match '^//\s*Time\s*:\s*(\d{4}-\d{2}-\d{2})') {
            try { return [datetime]::ParseExact($Matches[1], 'yyyy-MM-dd', $null) } catch { }
        }
    }
    return $null
}

if (-not (Test-Path $Root)) { throw "no such folder: $Root" }

$files = Get-ChildItem $Root -File -Filter *.cpp | Sort-Object Name
if (-not $files) { 'nothing to do'; return }

# ---------- pass 1: classify ----------
$info = @()
foreach ($f in $files) {
    $hd = Get-HeaderDate $f.FullName
    $info += [pscustomobject]@{
        File    = $f
        HasHead = ($null -ne $hd)
        Head    = $hd
        Mtime   = $f.LastWriteTime
        SecKey  = $f.LastWriteTime.ToString('yyyy-MM-dd HH:mm:ss')
    }
}

# ---------- artifact detection ----------
$secCount = @{}
foreach ($i in $info) {
    if (-not $i.HasHead) {
        $k = $i.SecKey
        if ($secCount.ContainsKey($k)) { $secCount[$k]++ } else { $secCount[$k] = 1 }
    }
}
$artifactSecs = @{}
foreach ($k in $secCount.Keys) {
    if ($secCount[$k] -ge $ArtifactThreshold) { $artifactSecs[$k] = $secCount[$k] }
}

# ---------- pass 2: plan ----------
$plan = @()
foreach ($i in $info) {
    $f = $i.File
    $empty = ($f.Length -eq 0)
    $isArtifact = (-not $i.HasHead) -and $artifactSecs.ContainsKey($i.SecKey)

    if ($isArtifact) {
        $target = Join-Path $oldDir 'unknown'
        $dateStr = 'unknown'
    } else {
        $d = if ($i.HasHead) { $i.Head } else { $i.Mtime }
        $target = Join-Path $oldDir ('{0}\{1}\{2}' -f $d.ToString('yyyy'), $d.ToString('MM'), $d.ToString('dd'))
        $dateStr = $d.ToString('yyyy-MM-dd')
    }
    if ($empty -and $Unaccept) { $target = $unacceptDir }

    $plan += [pscustomobject]@{
        File = $f.Name; Date = $dateStr; Empty = $empty; Artifact = $isArtifact
        Dest = (Join-Path $target $f.Name); Src = $f.FullName
    }
}

# ---------- report ----------
$dated = @($plan | Where-Object { -not $_.Artifact })
$undated = @($plan | Where-Object { $_.Artifact })

''
'--- dated files by year-month ---'
$dated | Group-Object { $_.Date.Substring(0, 7) } | Sort-Object Name |
    ForEach-Object { '  {0}   {1,3}' -f $_.Name, $_.Count }

''
'--- date source ---'
'  "// Time" header : {0,3}' -f @($info | Where-Object HasHead).Count
'  file mtime       : {0,3}' -f (@($dated).Count - @($info | Where-Object HasHead).Count)
'  artifact -> unknown : {0,3}' -f $undated.Count

''
'--- artifact timestamps (>= {0} headerless files at the same second) ---' -f $ArtifactThreshold
foreach ($k in ($artifactSecs.Keys | Sort-Object)) { '  {0}   x{1}' -f $k, $artifactSecs[$k] }

''
'--- 0-byte stubs ---'
$plan | Where-Object Empty | ForEach-Object { '  ' + $_.File }

''
'--- first 10 planned moves ---'
$plan | Select-Object -First 10 | ForEach-Object {
    '  {0,-22} {1,-10} ->  {2}' -f $_.File, $_.Date, $_.Dest.Substring($Root.Length + 1)
}
''
'  ... and {0} more' -f ($plan.Count - 10)

''
'Total {0} .cpp: {1} dated, {2} -> old\unknown\' -f $plan.Count, $dated.Count, $undated.Count

if (-not $Apply) { ''; 'dry run - pass -Apply to execute'; return }

# ---------- execute ----------
''
$moved = 0; $skipped = 0
foreach ($p in $plan) {
    if (-not (Test-Path $p.Src)) { "gone: $($p.Src)"; continue }
    if ((Test-Path $p.Dest) -and ((Get-FileHash $p.Dest).Hash -ne (Get-FileHash $p.Src).Hash)) {
        "CONFLICT, both exist and differ: $($p.Dest)"; $skipped++; continue
    }
    New-Item -ItemType Directory -Force -Path (Split-Path $p.Dest) | Out-Null
    Move-Item -LiteralPath $p.Src -Destination $p.Dest -Force
    Move-Cph $p.Src $p.Dest | Out-Null
    $moved++
}
''
"moved $moved file(s), skipped $skipped"
