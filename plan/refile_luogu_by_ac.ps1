# refile_luogu_by_ac.ps1 - re-date already-filed Luogu solutions using real submit dates
#
# The .cpp on disk is the LAST version written for that problem, not the first-AC
# version. So the right date is the **last submission of any status**, not the
# first AC. Example that forced this: P2669 was first AC'd 2020-12-25 (beginner
# days, no template) but last submitted 2024-11-26 with a full template -- dating
# it 2020-12-25 would claim he wrote a template while learning.
#
#   dated   : pid has at least one AC record -> old\<lastSubmit yyyy>\<MM>\<dd>\
#   neverAC : pid has no AC record at all    -> unaccept\
#             (still worked on, but never passed on this account)
#
# Resolution: basename -> candidate pids -> the pid map
#   exact basename / strip leading underscores / strip "Luogu_" prefix /
#   drop all underscores (AT_abc_382_c ~ ATabc382c) / strip -suffix
#
# Usage:
#   .\refile_luogu_by_ac.ps1            # dry run
#   .\refile_luogu_by_ac.ps1 -Apply

param(
    [switch]$Apply,
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

# ---------- load map ----------
$payload = [IO.File]::ReadAllText($AcJson, [Text.Encoding]::UTF8) | ConvertFrom-Json
$everAc = @{}
foreach ($prop in $payload.firstAc.PSObject.Properties) { $everAc[$prop.Name] = $prop.Value }
$lastDate = @{}
foreach ($prop in $payload.lastSubmit.PSObject.Properties) { $lastDate[$prop.Name] = $prop.Value }
if (-not $lastDate.Count) { throw 'lastSubmit is empty in ' + $AcJson }

$idxExact = @{}
$idxFlat = @{}
foreach ($k in $lastDate.Keys) {
    $idxExact[$k] = $k
    $n = $k -replace '_', ''
    if (-not $idxFlat.ContainsKey($n)) { $idxFlat[$n] = $k }
}
Write-Host ("map: {0} pids submitted, {1} ever AC, generated {2}" -f $lastDate.Count, $everAc.Count, $payload.generated)

function Resolve-Pid([string]$base) {
    $cands = New-Object System.Collections.Generic.List[string]
    $cands.Add($base)
    $s = $base -replace '^_+', ''
    $cands.Add($s)
    if ($s -match '^Luogu_(.+)$') {
        $r = $Matches[1]
        $cands.Add($r)
        $cands.Add(($r -replace '_', ''))
    }
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

# ---------- plan ----------
$files = Get-ChildItem $oldDir -Recurse -File -Filter *.cpp | Sort-Object FullName
if (-not $files) { 'no .cpp under old\ - nothing to do'; return }

$plan = @()
foreach ($f in $files) {
    $probId = Resolve-Pid $f.BaseName
    if ($probId -and $everAc.ContainsKey($probId)) {
        $d = [datetime]::ParseExact($lastDate[$probId], 'yyyy-MM-dd', $null)
        $targetDir = Join-Path $oldDir ('{0}\{1}\{2}' -f $d.ToString('yyyy'), $d.ToString('MM'), $d.ToString('dd'))
        $dest = Join-Path $targetDir $f.Name
        $tag = 'dated'; $why = $probId
    } else {
        $dest = Join-Path $unacceptDir $f.Name
        $tag = 'neverAC'; $why = $(if ($probId) { $probId } else { '-' })
    }
    $plan += [pscustomobject]@{
        File = $f.Name; Tag = $tag; Pid = $why; Src = $f.FullName; Dest = $dest
        Same = ($f.FullName -eq $dest)
    }
}

$moves = @($plan | Where-Object { -not $_.Same })
''
'--- classification ---'
$plan | Group-Object Tag | Sort-Object Name | ForEach-Object { '  {0,-10} {1,4}' -f $_.Name, $_.Count }
'  already correct    {0,4}' -f @($plan | Where-Object Same).Count
'  to move            {0,4}' -f $moves.Count

''
'--- will land in unaccept\ ---'
($plan | Where-Object { $_.Tag -eq 'neverAC' } | ForEach-Object { $_.File }) -join ' '

''
'--- sample of dated moves ---'
$moves | Where-Object { $_.Tag -eq 'dated' } | Select-Object -First 10 | ForEach-Object {
    '  {0,-24} ({1}) -> {2}' -f $_.File, $_.Pid, $_.Dest.Substring($Root.Length + 1)
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

# prune empty leaf dirs under old\
$empty = Get-ChildItem $oldDir -Recurse -Directory | Where-Object {
    $_.Name -match '^\d{2}$' -and (Get-ChildItem $_.FullName -Force | Measure-Object).Count -eq 0
}
$empty | Sort-Object { $_.FullName.Length } -Descending | ForEach-Object { Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue }

''
"moved $n file(s)"
