# redate_luogu.ps1 - final date rule for already-filed Luogu solutions
#
# Why this exists: two candidate dates, each wrong in a different case.
#
#   mtime      = when THIS file was last written.
#                Wrong when a bulk copy/restore stamped it (artifact).
#   lastSubmit = when the pid was last submitted.
#                Wrong when a DIFFERENT file was submitted under that pid --
#                e.g. P3375/P3376/P5357/P3808 are template problems he re-submitted
#                while rewriting the templates in 2026-11, but the .cpp on disk is
#                the untouched 2022/2023 original.
#
# So: mtime wins unless it is an artifact. Artifact fallbacks are header, then
# lastSubmit.
#
#   1. mtime is NOT an artifact second-cluster      -> mtime
#   2. mtime IS an artifact, "// Time" parses       -> header date
#   3. mtime IS an artifact, pid has a lastSubmit   -> lastSubmit date
#   4. none of the above                            -> unaccept\
#
# Artifact rule (same as organize_luogu.ps1): among the files WITHOUT a
# "// Time" header, >=3 sharing the exact same yyyy-MM-dd HH:mm:ss is a bulk
# copy/restore, not a real save.
#
# Only files currently under old\ are re-dated. Files in unaccept\ stay there
# (no AC on this account is a separate axis from the date).
#
# Usage:
#   .\redate_luogu.ps1            # dry run
#   .\redate_luogu.ps1 -Apply

param(
    [switch]$Apply,
    [int]$ArtifactThreshold = 3,
    [string]$Root = 'D:\code\OI\luogu\problems',
    [string]$AcJson = 'D:\code\plan\cache\luogu_ac.json'
)

$ErrorActionPreference = 'Stop'
$oldDir = Join-Path $Root 'old'
$unacceptDir = Join-Path $Root 'unaccept'

if (-not (Test-Path $AcJson)) { throw "missing $AcJson - run plan\fetch_luogu_ac.ps1 first" }

# ---------- cph helpers ----------
function Get-PathHash([string]$Path) {
    $md5 = [System.Security.Cryptography.MD5]::Create()
    try { $bytes = $md5.ComputeHash([Text.Encoding]::UTF8.GetBytes($Path)) }
    finally { $md5.Dispose() }
    ($bytes | ForEach-Object { $_.ToString('x2') }) -join ''
}
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
    if ((Test-Path $probTo) -and -not (Test-Path $probFrom)) { return 'ok' }
    if (-not (Test-Path $probFrom)) { return 'none' }
    $json = [IO.File]::ReadAllText($probFrom, [Text.Encoding]::UTF8) | ConvertFrom-Json
    $json.srcPath = Get-CphPath $To
    $cphDir = Split-Path $probTo -Parent
    if (-not (Test-Path $cphDir)) { New-Item -ItemType Directory -Force -Path $cphDir | Out-Null }
    [IO.File]::WriteAllText($probTo, ($json | ConvertTo-Json -Depth 20 -Compress),
        (New-Object System.Text.UTF8Encoding($false)))
    if ($probFrom -ne $probTo) {
        Remove-Item $probFrom -Force
        $fromDir = Split-Path $probFrom -Parent
        if ((Get-ChildItem $fromDir -Force | Measure-Object).Count -eq 0) { Remove-Item $fromDir -Force }
    }
    return 'moved'
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

# ---------- load pid map ----------
$payload = [IO.File]::ReadAllText($AcJson, [Text.Encoding]::UTF8) | ConvertFrom-Json
$everAc = @{}
foreach ($p in $payload.firstAc.PSObject.Properties) { $everAc[$p.Name] = $p.Value }
$lastDate = @{}
foreach ($p in $payload.lastSubmit.PSObject.Properties) { $lastDate[$p.Name] = $p.Value }

$idxExact = @{}; $idxFlat = @{}
foreach ($k in $lastDate.Keys) {
    $idxExact[$k] = $k
    $n = $k -replace '_', ''
    if (-not $idxFlat.ContainsKey($n)) { $idxFlat[$n] = $k }
}
function Resolve-Pid([string]$base) {
    $cands = New-Object System.Collections.Generic.List[string]
    $cands.Add($base)
    $s = $base -replace '^_+', ''
    $cands.Add($s)
    if ($s -match '^Luogu_(.+)$') { $r = $Matches[1]; $cands.Add($r); $cands.Add(($r -replace '_', '')) }
    $cands.Add(($base -replace '_', ''))
    $cands.Add(($s -replace '[-_].*$', ''))
    $cands.Add(($s -replace '_+$', ''))
    foreach ($c in $cands) {
        if (-not $c) { continue }
        if ($idxExact.ContainsKey($c)) { return $c }
        $n = $c -replace '_', ''
        if ($idxFlat.ContainsKey($n)) { return $idxFlat[$n] }
    }
    return $null
}

# ---------- gather + artifact detection over the WHOLE tree ----------
$all = Get-ChildItem $Root -Recurse -File -Filter *.cpp | Sort-Object FullName
$meta = @()
foreach ($f in $all) {
    $hd = Get-HeaderDate $f.FullName
    $meta += [pscustomobject]@{
        File = $f; Header = $hd; HasHeader = ($null -ne $hd)
        Mtime = $f.LastWriteTime; SecKey = $f.LastWriteTime.ToString('yyyy-MM-dd HH:mm:ss')
    }
}
$secCount = @{}
foreach ($m in $meta) {
    if ($m.HasHeader) { continue }
    $k = $m.SecKey
    if ($secCount.ContainsKey($k)) { $secCount[$k]++ } else { $secCount[$k] = 1 }
}
$artifact = @{}
foreach ($k in $secCount.Keys) { if ($secCount[$k] -ge $ArtifactThreshold) { $artifact[$k] = $secCount[$k] } }

Write-Host ("tree: {0} .cpp; artifact seconds: {1} covering {2} files" -f `
    $all.Count, $artifact.Count, (@($artifact.Values) | Measure-Object -Sum).Sum)

# ---------- plan: only files currently under old\ ----------
$plan = @()
foreach ($m in $meta) {
    if ($m.File.FullName -notlike (Join-Path $oldDir '*')) { continue }
    $isArt = (-not $m.HasHeader) -and $artifact.ContainsKey($m.SecKey)

    if (-not $isArt) {
        $d = $m.Mtime; $src = 'mtime'
    } elseif ($m.HasHeader) {
        $d = $m.Header; $src = 'header'
    } else {
        $probId = Resolve-Pid $m.File.BaseName
        if ($probId -and $lastDate.ContainsKey($probId)) {
            $d = [datetime]::ParseExact($lastDate[$probId], 'yyyy-MM-dd', $null); $src = 'lastSubmit'
        } else {
            $d = $null; $src = 'none'
        }
    }

    if ($null -eq $d) {
        $dest = Join-Path $unacceptDir $m.File.Name
    } else {
        $dest = Join-Path (Join-Path $oldDir ('{0}\{1}\{2}' -f $d.ToString('yyyy'), $d.ToString('MM'), $d.ToString('dd'))) $m.File.Name
    }
    $plan += [pscustomobject]@{
        File = $m.File.Name; Src = $m.File.FullName; Dest = $dest; From = $src
        Date = $(if ($null -eq $d) { 'unaccept' } else { $d.ToString('yyyy-MM-dd') })
        Same = ($m.File.FullName -eq $dest)
    }
}

$moves = @($plan | Where-Object { -not $_.Same })
''
'--- date source used ---'
$plan | Group-Object From | Sort-Object Name | ForEach-Object { '  {0,-10} {1,4}' -f $_.Name, $_.Count }
''
'  already correct  {0,4}' -f @($plan | Where-Object Same).Count
'  to move          {0,4}' -f $moves.Count

''
'--- moves ---'
$moves | Sort-Object File |
    Select-Object -First 25 | ForEach-Object {
        '  {0,-20} {1,-12} -> {2}   [{3}]' -f $_.File, $_.Date, $_.Dest.Substring($Root.Length + 1), $_.From
    }

if (-not $Apply) { ''; 'dry run - pass -Apply to execute'; return }

''
$n = 0
foreach ($p in $moves) {
    if (-not (Test-Path $p.Src)) { "gone: $($p.Src)"; continue }
    if ((Test-Path $p.Dest) -and ((Get-FileHash $p.Dest).Hash -ne (Get-FileHash $p.Src).Hash)) {
        "CONFLICT: $($p.Dest)"; continue
    }
    New-Item -ItemType Directory -Force -Path (Split-Path $p.Dest) | Out-Null
    Move-Item -LiteralPath $p.Src -Destination $p.Dest -Force
    Move-Cph $p.Src $p.Dest | Out-Null
    $n++
}

$empty = Get-ChildItem $oldDir -Recurse -Directory | Where-Object {
    $_.Name -match '^\d{2}$' -and (Get-ChildItem $_.FullName -Force | Measure-Object).Count -eq 0
}
$empty | Sort-Object { $_.FullName.Length } -Descending | ForEach-Object { Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue }

''
"moved $n file(s)"
