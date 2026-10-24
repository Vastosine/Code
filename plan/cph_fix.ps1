# cph_fix.ps1 - re-key cph metadata after moving solution files around
#
#   Competitive Programming Helper stores one file per source file:
#       .cph\.<fileName>_<md5(lowercase-drive path)>.prob
#   with the source path inside as "srcPath".
#   Moving a .cpp therefore breaks the link twice (file name hash + srcPath).
#   This script finds the entry by file NAME (not by hash), rewrites srcPath
#   and renames the entry to the hash of the new path.
#
# Usage:
#   .\cph_fix.ps1            # dry run
#   .\cph_fix.ps1 -Apply

param(
    [switch]$Apply,
    [string]$Root = 'D:\code\OI\codeforces'
)

$ErrorActionPreference = 'Stop'
$cphDir = Join-Path $Root '.cph'
if (-not (Test-Path $cphDir)) { throw "no $cphDir" }

function Get-PathHash([string]$Path) {
    $md5 = [System.Security.Cryptography.MD5]::Create()
    try { $bytes = $md5.ComputeHash([Text.Encoding]::UTF8.GetBytes($Path)) }
    finally { $md5.Dispose() }
    ($bytes | ForEach-Object { $_.ToString('x2') }) -join ''
}

# cph writes the drive letter lower-case, everything else verbatim
function Get-CphPath([string]$Path) { $Path.Substring(0, 1).ToLower() + $Path.Substring(1) }

# index every .prob entry by the source file name it belongs to
$entries = @{}
foreach ($f in (Get-ChildItem $cphDir -File -Filter *.prob)) {
    if ($f.Name -notmatch '^\.(.+)_([0-9a-f]{32})\.prob$') { continue }
    $leaf = $Matches[1]
    try { $json = Get-Content $f.FullName -Raw | ConvertFrom-Json } catch { continue }
    if (-not $entries.ContainsKey($leaf)) { $entries[$leaf] = @() }
    $entries[$leaf] += [pscustomobject]@{
        File  = $f
        Json  = $json
        Tests = @($json.tests).Count
        Path  = [string]$json.srcPath
    }
}

$changed = 0
$orphans = @()
foreach ($cpp in (Get-ChildItem $Root -Recurse -File -Filter *.cpp | Where-Object { $_.FullName -notlike '*\.cph\*' })) {
    $src = Get-CphPath $cpp.FullName
    $want = Join-Path $cphDir ('.{0}_{1}.prob' -f $cpp.Name, (Get-PathHash $src))

    if (-not $entries.ContainsKey($cpp.Name)) {
        $orphans += $cpp.FullName
        continue
    }

    # prefer the entry whose srcPath already points here, then the richest one
    $best = $entries[$cpp.Name] |
            Sort-Object -Property @{ Expression = { if ($_.Path -eq $src) { 0 } else { 1 } } },
                                  @{ Expression = { - $_.Tests } } |
            Select-Object -First 1
    $stale = @($entries[$cpp.Name] | Where-Object { $_.File.FullName -ne $best.File.FullName })

    $rel = $want.Substring($Root.Length + 1)
    if ($best.Path -eq $src -and $best.File.FullName -eq $want -and $stale.Count -eq 0) { continue }

    "FIX {0,-56} tests={1,-3} {2}" -f $cpp.Name, $best.Tests, $rel
    if (-not $Apply) { $changed++; continue }

    $best.Json.srcPath = $src
    $best.Json | ConvertTo-Json -Depth 20 -Compress | Set-Content $want -Encoding utf8 -NoNewline
    foreach ($s in @($stale) + @($best) ) {
        if ($s.File.FullName -ne $want -and (Test-Path $s.File.FullName)) { Remove-Item $s.File.FullName -Force }
    }
    $changed++
}

if ($orphans.Count) {
    ''
    "no cph entry for:"
    $orphans | ForEach-Object { "  $_" }
}

''
if ($Apply) { "fixed $changed entr(ies)" } else { "would fix $changed entr(ies) - pass -Apply" }
