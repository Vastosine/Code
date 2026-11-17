# refile_luogu_by_ac.ps1 - re-date already-filed Luogu solutions using real AC dates
#
# Step 2 of the Luogu cleanup. organize_luogu.ps1 filed everything by a
# "// Time" header or the file mtime (approximate). Now that
# plan\cache\luogu_ac.json holds the first-AC date for every pid (fetched from
# the Luogu record list), this re-files each .cpp by its REAL first-AC date.
#
# Resolution:   basename -> candidate pids -> AC map
#   * exact basename
#   * strip leading underscores / "Luogu_" prefix
#   * drop underscores entirely (AT_abc_382_c ~ ATabc382c)
#   * strip a -suffix or trailing underscores (P1090-biaozhun -> P1090)
#   If nothing resolves, the problem was never AC'd -> unaccept\
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

# ---------- cph helpers (same as organize_luogu.ps1) ----------
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

# ---------- load AC map ----------
$payload = [IO.File]::ReadAllText($AcJson, [Text.Encoding]::UTF8) | ConvertFrom-Json
$acExact = @{}
foreach ($prop in $payload.ac.PSObject.Properties) { $acExact[$prop.Name] = $prop.Value }
$acNoUnderscore = @{}
foreach ($k in $acExact.Keys) {
    $n = $k -replace '_', ''
    if (-not $acNoUnderscore.ContainsKey($n)) { $acNoUnderscore[$n] = $k }
}
Write-Host ("AC map: {0} pids, generated {1}" -f $acExact.Count, $payload.generated)

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
        if ($acExact.ContainsKey($c)) { return @{ pid = $c; how = 'exact' } }
        $n = $c -replace '_', ''
        if ($acNoUnderscore.ContainsKey($n)) { return @{ pid = $acNoUnderscore[$n]; how = 'nounderscore' } }
    }
    return $null
}

# ---------- plan ----------
$files = Get-ChildItem $oldDir -Recurse -File -Filter *.cpp | Sort-Object FullName
if (-not $files) { 'no .cpp under old\ - nothing to do'; return }

$plan = @()
foreach ($f in $files) {
    $hit = Resolve-Pid $f.BaseName
    if ($hit) {
        $d = [datetime]::ParseExact($acExact[$hit.pid], 'yyyy-MM-dd', $null)
        $targetDir = Join-Path $oldDir ('{0}\{1}\{2}' -f $d.ToString('yyyy'), $d.ToString('MM'), $d.ToString('dd'))
        $dest = Join-Path $targetDir $f.Name
        $tag = 'dated'
        $why = $hit.pid
    } else {
        $dest = Join-Path $unacceptDir $f.Name
        $tag = 'neverAC'
        $why = '-'
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
'--- unresolved (never AC on this account) -> unaccept\ ---'
($plan | Where-Object { $_.Tag -eq 'neverAC' } | ForEach-Object { $_.File }) -join ' '

''
'--- sample of dated moves ---'
$moves | Where-Object { $_.Tag -eq 'dated' } | Select-Object -First 8 | ForEach-Object {
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

# prune empty date dirs
$empty = Get-ChildItem $oldDir -Recurse -Directory | Where-Object { $_.Name -match '^\d{2}$' -and (Get-ChildItem $_.FullName -Force | Measure-Object).Count -eq 0 }
$empty | Sort-Object { $_.FullName.Length } -Descending | ForEach-Object { Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue }

''
"moved $n file(s)"
