# cph_fix.ps1 - re-key cph metadata after moving solution files around
#
#   Competitive Programming Helper stores one file per source file:
#       .cph\.<fileName>_<md5(lowercase-drive path)>.prob
#   with the source path inside as "srcPath".
#   Moving a .cpp therefore breaks the link twice (file name hash + srcPath).
#   This script finds the entry by file NAME (not by hash), rewrites srcPath
#   and renames the entry to the hash of the new path.
#
#   Every ".cph" directory found under -Root is handled; a source file belongs
#   to the deepest ".cph" directory above it.
#
# Usage:
#   .\cph_fix.ps1                                  # dry run, OI\codeforces
#   .\cph_fix.ps1 -Apply
#   .\cph_fix.ps1 -Root 'D:\code\OI\contests' -Apply   # all contest sets

param(
    [switch]$Apply,
    [string]$Root = 'D:\code\OI\codeforces'
)

$ErrorActionPreference = 'Stop'

function Get-PathHash([string]$Path) {
    $md5 = [System.Security.Cryptography.MD5]::Create()
    try { $bytes = $md5.ComputeHash([Text.Encoding]::UTF8.GetBytes($Path)) }
    finally { $md5.Dispose() }
    ($bytes | ForEach-Object { $_.ToString('x2') }) -join ''
}

# cph writes the drive letter lower-case, everything else verbatim
function Get-CphPath([string]$Path) { $Path.Substring(0, 1).ToLower() + $Path.Substring(1) }

# cph parses its state with JSON.parse, so the file must be UTF-8 WITHOUT BOM
function Write-CphJson([string]$Path, $Json) {
    $text = $Json | ConvertTo-Json -Depth 20 -Compress
    [IO.File]::WriteAllText($Path, $text, (New-Object System.Text.UTF8Encoding($false)))
}

function Test-Bom([string]$Path) {
    if (-not (Test-Path $Path)) { return $false }
    $b = [IO.File]::ReadAllBytes($Path)
    $b.Length -ge 3 -and $b[0] -eq 0xEF -and $b[1] -eq 0xBB -and $b[2] -eq 0xBF
}

$cphDirs = @(Get-ChildItem $Root -Recurse -Directory -Filter '.cph' -ErrorAction SilentlyContinue)
if (Test-Path (Join-Path $Root '.cph')) { $cphDirs += Get-Item (Join-Path $Root '.cph') }
if (-not $cphDirs) { throw "no .cph directory under $Root" }

# leaf name -> list of entries, per .cph directory
$index = @{}
foreach ($dir in $cphDirs) {
    $table = @{}
    foreach ($f in (Get-ChildItem $dir.FullName -File -Filter *.prob)) {
        if ($f.Name -notmatch '^\.(.+)_([0-9a-f]{32})\.prob$') { continue }
        $leaf = $Matches[1]
        try { $json = [IO.File]::ReadAllText($f.FullName, [Text.Encoding]::UTF8) | ConvertFrom-Json } catch { continue }
        if (-not $table.ContainsKey($leaf)) { $table[$leaf] = @() }
        $table[$leaf] += [pscustomobject]@{
            File  = $f
            Json  = $json
            Tests = @($json.tests).Count
            Path  = [string]$json.srcPath
        }
    }
    $index[$dir.FullName] = $table
}

function Get-Owner([string]$File) {
    $best = $null
    foreach ($dir in $cphDirs) {
        $base = Split-Path $dir.FullName -Parent
        if ($File.StartsWith($base, [StringComparison]::OrdinalIgnoreCase)) {
            if (-not $best -or $base.Length -gt (Split-Path $best -Parent).Length) { $best = $dir.FullName }
        }
    }
    $best
}

$changed = 0
$orphans = @()
foreach ($cpp in (Get-ChildItem $Root -Recurse -File -Filter *.cpp | Where-Object { $_.FullName -notlike '*\.cph\*' })) {
    $owner = Get-Owner $cpp.FullName
    if (-not $owner) { $orphans += $cpp.FullName; continue }
    $table = $index[$owner]
    if (-not $table.ContainsKey($cpp.Name)) { $orphans += $cpp.FullName; continue }

    $src = Get-CphPath $cpp.FullName
    $want = Join-Path $owner ('.{0}_{1}.prob' -f $cpp.Name, (Get-PathHash $src))

    # prefer the entry whose srcPath already points here, then the richest one
    $best = $table[$cpp.Name] |
            Sort-Object -Property @{ Expression = { if ($_.Path -eq $src) { 0 } else { 1 } } },
                                  @{ Expression = { - $_.Tests } } |
            Select-Object -First 1
    $stale = @($table[$cpp.Name] | Where-Object { $_.File.FullName -ne $best.File.FullName })

    if ($best.Path -eq $src -and $best.File.FullName -eq $want -and $stale.Count -eq 0 -and
        -not (Test-Bom $want)) { continue }

    "FIX {0,-56} tests={1,-3} {2}" -f $cpp.Name, $best.Tests, (($want -replace [regex]::Escape($Root), '').TrimStart('\'))
    if (-not $Apply) { $changed++; continue }

    $best.Json.srcPath = $src
    Write-CphJson $want $best.Json
    foreach ($s in @($stale) + @($best)) {
        if ($s.File.FullName -ne $want -and (Test-Path $s.File.FullName)) { Remove-Item $s.File.FullName -Force }
    }
    $changed++
}

if ($orphans.Count) {
    ''
    'no cph entry for:'
    $orphans | ForEach-Object { "  $_" }
}

''
if ($Apply) { "fixed $changed entr(ies)" } else { "would fix $changed entr(ies) - pass -Apply" }
