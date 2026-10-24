# stress.ps1 - random stress test for competitive programming.
#
# Usage:
#   .\stress.ps1 -Sol a.cpp -N 300
#   .\stress.ps1 -Sol main            # extension .cpp is added automatically
#   .\stress.ps1 -Sol a.cpp -Brute b -Gen gen -N 500   # override the shared pair
#   .\stress.ps1 -Sol a.cpp -Keep -N 20                # keep every case's in/out
#
# Convention:
#   gen.cpp    reads one integer seed from argv[1], prints a test case to stdout
#   brute.cpp  reads the test case from stdin, prints the answer to stdout
#   sol.cpp    same interface as brute.cpp, this is the program under test
#
# Each source gets its own build folder (stress_out\build\<hash of path>), so
# switching -Sol never reuses a binary compiled from a different file.
# On a mismatch the input, the sol output and the brute output are all saved
# as stress_out\fail_<case>_<seed>.{in,out,brute.out}, and the first differing
# token is printed.
#
# gen.cpp and brute.cpp default to the folder where this script lives
# (D:\code\stress), so the sol file can be anywhere. -Sol / -Brute / -Gen
# accept any file name, and the .cpp extension is optional.
#
# Exit codes: 0 = all tests passed, 1 = mismatch / RE / TLE found, 2 = setup error.

[CmdletBinding()]
param(
    [string]$Sol = 'sol.cpp',
    [string]$Brute = '',
    [string]$Gen = '',
    [int]$N = 200,
    [int]$Seed = 0,
    [int]$TimeoutMs = 2000,
    [switch]$Strict,
    [switch]$Keep,
    [string]$OutDir = ''
)

$ErrorActionPreference = 'Stop'

# gen.cpp / brute.cpp live next to this script by default.
if (-not $Brute) { $Brute = Join-Path $PSScriptRoot 'brute.cpp' }
if (-not $Gen) { $Gen = Join-Path $PSScriptRoot 'gen.cpp' }

function Die([string]$msg) {
    Write-Host "[stress] $msg" -ForegroundColor Red
    exit 2
}

if ($N -lt 1) { Die '-N must be >= 1' }

# Output (compiled exe, in.txt, fail_*.in) goes into D:\code\stress\stress_out
# by default, so it does not litter the problem folder. Override with -OutDir.
if (-not $OutDir) { $OutDir = Join-Path $PSScriptRoot 'stress_out' }
if (-not (Test-Path -LiteralPath $OutDir)) {
    New-Item -ItemType Directory -Path $OutDir -Force | Out-Null
}
$OutDir = (Resolve-Path -LiteralPath $OutDir).Path

# "-Sol a" is accepted as a shorthand for "a.cpp".
function Add-CppExt([string]$p) {
    if ((Test-Path -LiteralPath $p) -or [IO.Path]::HasExtension($p)) { return $p }
    $q = $p + '.cpp'
    if (Test-Path -LiteralPath $q) { return $q }
    return $p
}
$Sol = Add-CppExt $Sol
$Brute = Add-CppExt $Brute
$Gen = Add-CppExt $Gen

foreach ($pair in @(@($Sol, 'sol'), @($Brute, 'brute'), @($Gen, 'gen'))) {
    if (-not (Test-Path -LiteralPath $pair[0])) {
        Die ("{0} not found: {1}" -f $pair[1], $pair[0])
    }
}
$SolSrc = (Resolve-Path -LiteralPath $Sol).Path
$BruteSrc = (Resolve-Path -LiteralPath $Brute).Path
$GenSrc = (Resolve-Path -LiteralPath $Gen).Path

$CXX = 'clang++'
if (-not (Get-Command $CXX -ErrorAction SilentlyContinue)) { $CXX = 'g++' }
if (-not (Get-Command $CXX -ErrorAction SilentlyContinue)) { Die 'no C++ compiler found (clang++ / g++)' }

# Each source file gets its OWN build folder, keyed by its full path.
# A single shared sol.exe would be silently reused when you switch -Sol to a
# different file whose timestamp is older than the last build (the exe looks
# "newer than the source" so the rebuild is skipped and you benchmark the
# wrong binary). Keying by path makes that impossible.
function Get-SourceKey([string]$src) {
    $sha = [System.Security.Cryptography.SHA1]::Create()
    try { $bytes = $sha.ComputeHash([Text.Encoding]::UTF8.GetBytes($src.ToLower())) }
    finally { $sha.Dispose() }
    (($bytes | ForEach-Object { $_.ToString('x2') }) -join '').Substring(0, 12)
}

function Build([string]$src, [string]$tag) {
    $dir = Join-Path $OutDir ('build\' + (Get-SourceKey $src))
    if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    $exe = Join-Path $dir ($tag + '.exe')
    if ((Test-Path -LiteralPath $exe) -and
        ((Get-Item -LiteralPath $exe).LastWriteTime -ge (Get-Item -LiteralPath $src).LastWriteTime)) {
        return $exe
    }
    Write-Host ("[stress] building {0} ..." -f (Split-Path $src -Leaf)) -ForegroundColor DarkGray
    $sw = [Diagnostics.Stopwatch]::StartNew()
    & $CXX -std=c++20 -O2 $src -o $exe
    $code = $LASTEXITCODE
    $sw.Stop()
    if ($code -ne 0) { Die ("compile failed: {0}" -f $src) }
    Write-Host ("[stress] built in {0:N1}s" -f $sw.Elapsed.TotalSeconds) -ForegroundColor DarkGray
    return $exe
}

$SolExe = Build $SolSrc 'sol'
$BruteExe = Build $BruteSrc 'brute'
$GenExe = Build $GenSrc 'gen'
Write-Host ("[stress] sol   = {0}" -f $SolSrc) -ForegroundColor DarkGray
Write-Host ("[stress] brute = {0}" -f $BruteSrc) -ForegroundColor DarkGray
Write-Host ("[stress] gen   = {0}" -f $GenSrc) -ForegroundColor DarkGray

$InFile = Join-Path $OutDir 'in.txt'
$SolOut = Join-Path $OutDir 'sol.out'
$BruteOut = Join-Path $OutDir 'brute.out'
$SolErr = Join-Path $OutDir 'sol.err'
$BruteErr = Join-Path $OutDir 'brute.err'
$GenErr = Join-Path $OutDir 'gen.err'
$NullIn = Join-Path $OutDir 'nul.in'
Set-Content -LiteralPath $NullIn -Value '' -Encoding ASCII

function Invoke-Program([string]$exe, [string]$stdin, [string]$stdout, [string]$stderr, [int]$limitMs, [string]$argLine = '') {
    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $exe
    $psi.Arguments = $argLine
    $psi.UseShellExecute = $false
    $psi.CreateNoWindow = $true
    $psi.RedirectStandardInput = $true
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true

    $p = New-Object System.Diagnostics.Process
    $p.StartInfo = $psi
    [void]$p.Start()

    $outTask = $p.StandardOutput.ReadToEndAsync()
    $errTask = $p.StandardError.ReadToEndAsync()

    $inText = [IO.File]::ReadAllText($stdin)
    if ($inText.Length -gt 0) { $p.StandardInput.Write($inText) }
    $p.StandardInput.Close()

    if (-not $p.WaitForExit($limitMs)) {
        try { $p.Kill() } catch { }
        try { [void]$p.WaitForExit(2000) } catch { }
        return 'TLE'
    }

    [IO.File]::WriteAllText($stdout, $outTask.Result)
    [IO.File]::WriteAllText($stderr, $errTask.Result)

    if ($p.ExitCode -ne 0) { return ('RE:' + $p.ExitCode) }
    return 'OK'
}

function Normalize([string]$path) {
    $t = [IO.File]::ReadAllText($path)
    $parts = [Text.RegularExpressions.Regex]::Split($t.Trim(), '\s+')
    return ($parts -join ' ')
}

function ByteEqual([string]$a, [string]$b) {
    $ha = (Get-FileHash -LiteralPath $a -Algorithm SHA256).Hash
    $hb = (Get-FileHash -LiteralPath $b -Algorithm SHA256).Hash
    return $ha -eq $hb
}

function Show-Head([string]$path, [int]$lines) {
    if (-not (Test-Path -LiteralPath $path)) { return }
    $c = @(Get-Content -LiteralPath $path -TotalCount $lines)
    if ($c.Count -gt 0) { $c | ForEach-Object { Write-Host ('    ' + $_) -ForegroundColor DarkYellow } }
}

if ($Seed -gt 0) { $base = $Seed } else { $base = Get-Random -Minimum 1 -Maximum 2000000000 }

Write-Host ("[stress] sol={0}  brute={1}  gen={2}" -f (Split-Path $SolSrc -Leaf), (Split-Path $BruteSrc -Leaf), (Split-Path $GenSrc -Leaf)) -ForegroundColor Cyan
Write-Host ("[stress] cases={0}  timeout={1}ms  base-seed={2}  mode={3}" -f $N, $TimeoutMs, $base, $(if ($Strict) { 'byte' } else { 'token' })) -ForegroundColor Cyan

$total = [Diagnostics.Stopwatch]::StartNew()
$lastTick = 0

for ($i = 1; $i -le $N; $i++) {
    $seed = $base + $i - 1

    $r = Invoke-Program $GenExe $NullIn $InFile $GenErr 20000 ([string]$seed)
    if ($r -ne 'OK') {
        Write-Host ("[stress] generator failed ({0}) on seed {1}" -f $r, $seed) -ForegroundColor Red
        Show-Head $GenErr 10
        exit 1
    }
    if ((Get-Item -LiteralPath $InFile).Length -eq 0) {
        Write-Host ("[stress] generator produced empty output on seed {0}" -f $seed) -ForegroundColor Red
        exit 1
    }

    $solResult = Invoke-Program $SolExe $InFile $SolOut $SolErr $TimeoutMs
    if ($solResult -ne 'OK') {
        $bad = Join-Path $OutDir ("fail_{0}_{1}.in" -f $i, $seed)
        Copy-Item -LiteralPath $InFile -Destination $bad -Force
        Write-Host ""
        Write-Host ("[stress] case #{0} (seed {1}): solution {2}" -f $i, $seed, $solResult) -ForegroundColor Red
        Write-Host ("[stress] input saved to {0}" -f $bad) -ForegroundColor Red
        Show-Head $SolErr 8
        Write-Host ("[stress] reproduce: .\stress.ps1 -Seed {0} -N 1" -f $seed) -ForegroundColor Yellow
        exit 1
    }

    $bruteResult = Invoke-Program $BruteExe $InFile $BruteOut $BruteErr ($TimeoutMs * 3)
    if ($bruteResult -ne 'OK') {
        Write-Host ("[stress] case #{0}: brute {1} - brute is too slow or buggy, raise -TimeoutMs" -f $i, $bruteResult) -ForegroundColor Red
        Show-Head $BruteErr 8
        exit 1
    }

    if ($Strict) {
        $same = ByteEqual $SolOut $BruteOut
    }
    else {
        $same = (Normalize $SolOut) -ceq (Normalize $BruteOut)
    }

    if (-not $same) {
        $badIn = Join-Path $OutDir ("fail_{0}_{1}.in" -f $i, $seed)
        $badOut = Join-Path $OutDir ("fail_{0}_{1}.out" -f $i, $seed)
        $badBr = Join-Path $OutDir ("fail_{0}_{1}.brute.out" -f $i, $seed)
        Copy-Item -LiteralPath $InFile -Destination $badIn -Force
        Copy-Item -LiteralPath $SolOut -Destination $badOut -Force
        Copy-Item -LiteralPath $BruteOut -Destination $badBr -Force

        # compare token by token: a character offset is useless for numbers
        $nA = Normalize $SolOut
        $nB = Normalize $BruteOut
        $tokA = if ($nA) { @($nA -split ' ') } else { @() }
        $tokB = if ($nB) { @($nB -split ' ') } else { @() }
        $pos = 0
        while ($pos -lt $tokA.Count -and $pos -lt $tokB.Count -and $tokA[$pos] -ceq $tokB[$pos]) { $pos++ }

        Write-Host ""
        Write-Host ("[stress] WRONG ANSWER on case #{0} (seed {1})" -f $i, $seed) -ForegroundColor Red
        Write-Host ("  first different token: #{0} (1-based {1})" -f $pos, ($pos + 1)) -ForegroundColor Yellow
        $from = [Math]::Max(0, $pos - 4)
        $to = $pos + 5
        $segA = for ($k = $from; $k -lt [Math]::Min($to, $tokA.Count); $k++) { $tokA[$k] }
        $segB = for ($k = $from; $k -lt [Math]::Min($to, $tokB.Count); $k++) { $tokB[$k] }
        Write-Host ("  sol  : {0}" -f (@($segA) -join ' ')) -ForegroundColor Yellow
        Write-Host ("  brute: {0}" -f (@($segB) -join ' ')) -ForegroundColor Yellow
        Write-Host ("  tokens: sol={0}  brute={1}" -f $tokA.Count, $tokB.Count) -ForegroundColor DarkGray
        Write-Host ("  input  : {0}" -f $badIn) -ForegroundColor Red
        Write-Host ("  sol out: {0}" -f $badOut) -ForegroundColor Red
        Write-Host ("  brute  : {0}" -f $badBr) -ForegroundColor Red
        Write-Host ("  reproduce: .\stress.ps1 -Seed {0} -N 1" -f $seed) -ForegroundColor Yellow
        exit 1
    }

    if ($Keep) {
        $kd = Join-Path $OutDir ('keep\' + ("{0}_{1}" -f $i, $seed))
        New-Item -ItemType Directory -Path $kd -Force | Out-Null
        Copy-Item -LiteralPath $InFile -Destination (Join-Path $kd 'in.txt') -Force
        Copy-Item -LiteralPath $SolOut -Destination (Join-Path $kd 'sol.txt') -Force
        Copy-Item -LiteralPath $BruteOut -Destination (Join-Path $kd 'brute.txt') -Force
    }

    if ($N -ge 20) {
        $tick = [int](10.0 * $i / $N)
        if ($tick -ne $lastTick) {
            $lastTick = $tick
            Write-Host ("  {0,3}%" -f ($tick * 10)) -NoNewline
            Write-Host ("  ({0}/{1})" -f $i, $N) -ForegroundColor DarkGray
        }
    }
}

$total.Stop()
Write-Host ""
Write-Host ("[stress] all {0} cases passed in {1:N1}s" -f $N, $total.Elapsed.TotalSeconds) -ForegroundColor Green
exit 0
