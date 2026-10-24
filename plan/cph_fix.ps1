# cph_fix.ps1 - (re)build cph metadata for solution files
#
#   Competitive Programming Helper looks for its state next to the source file
#   (see getProbSaveLocation in the extension):
#       <dir of the .cpp>\.cph\.<fileName>_<md5(sourcePath)>.prob
#   and the file must be UTF-8 WITHOUT BOM, because it does JSON.parse().
#   Moving or renaming a .cpp therefore breaks the link twice.
#
#   This script finds an entry by file NAME (searching every .cph under -Root),
#   rewrites "srcPath", re-hashes it and puts it in the right folder.
#
# Usage:
#   .\cph_fix.ps1                                         # dry run, OI\codeforces
#   .\cph_fix.ps1 -Apply
#   .\cph_fix.ps1 -Root 'D:\code\OI\contests' -Apply      # every contest set

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

# cph stores the drive letter lower-case, everything else verbatim
function Get-CphPath([string]$Path) { $Path.Substring(0, 1).ToLower() + $Path.Substring(1) }

function Write-CphJson([string]$Path, $Json) {
    $dir = Split-Path $Path -Parent
    if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    [IO.File]::WriteAllText($Path, ($Json | ConvertTo-Json -Depth 20 -Compress),
        (New-Object System.Text.UTF8Encoding($false)))
}

function Test-Bom([string]$Path) {
    if (-not (Test-Path $Path)) { return $false }
    $b = [IO.File]::ReadAllBytes($Path)
    $b.Length -ge 3 -and $b[0] -eq 0xEF -and $b[1] -eq 0xBB -and $b[2] -eq 0xBF
}

# index every entry under every .cph dir, by source file name
$index = @{}
foreach ($dir in (Get-ChildItem $Root -Recurse -Directory -Filter '.cph')) {
    foreach ($f in (Get-ChildItem $dir.FullName -File -Filter *.prob)) {
        if ($f.Name -notmatch '^\.(.+)_([0-9a-f]{32})\.prob$') { continue }
        $leaf = $Matches[1]
        try { $json = [IO.File]::ReadAllText($f.FullName, [Text.Encoding]::UTF8) | ConvertFrom-Json }
        catch { continue }
        if (-not $index.ContainsKey($leaf)) { $index[$leaf] = @() }
        $index[$leaf] += [pscustomobject]@{
            File  = $f
            Json  = $json
            Tests = @($json.tests).Count
            Path  = [string]$json.srcPath
        }
    }
}

$changed = 0
$orphans = @()
$seen = @{}
foreach ($cpp in (Get-ChildItem $Root -Recurse -File -Filter *.cpp | Where-Object { $_.FullName -notlike '*\.cph\*' })) {
    $seen[$cpp.Name] = $true
    if (-not $index.ContainsKey($cpp.Name)) { $orphans += $cpp.FullName; continue }

    $src = Get-CphPath $cpp.FullName
    $want = Join-Path (Join-Path (Split-Path $cpp.FullName -Parent) '.cph') `
                     ('.{0}_{1}.prob' -f $cpp.Name, (Get-PathHash $src))

    # prefer the entry that already points here, then the richest one
    $best = $index[$cpp.Name] |
            Sort-Object -Property @{ Expression = { if ($_.Path -eq $src) { 0 } else { 1 } } },
                                  @{ Expression = { - $_.Tests } } |
            Select-Object -First 1
    $extra = @($index[$cpp.Name] | Where-Object { $_.File.FullName -ne $best.File.FullName })

    $inPlace = (Test-Path $want) -and (-not (Test-Bom $want)) -and
               ($best.File.FullName -eq $want) -and ($best.Path -eq $src) -and ($extra.Count -eq 0)
    if ($inPlace) { continue }

    "FIX {0,-56} tests={1,-3} -> {2}" -f $cpp.Name, $best.Tests, (Split-Path $want -Parent).Substring($Root.Length + 1)
    if (-not $Apply) { $changed++; continue }

    $best.Json.srcPath = $src
    Write-CphJson $want $best.Json
    foreach ($s in @($extra) + @($best)) {
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
