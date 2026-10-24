# stress.ps1 - random stress test for competitive programming.
#
# Usage:
#   .\stress.ps1 -Sol a.cpp -N 300
#   .\stress.ps1 -Sol main            # extension .cpp is added automatically
#   .\stress.ps1 -Sol a.cpp -Brute b -Gen gen -N 500   # override the shared pair
#   .\stress.ps1 -Sol a.cpp -Keep -N 20                # keep every case's in/out
#   .\stress.ps1 -Sol a.cpp -Check check -N 200        # constructive problems
#
# Checker mode (-Check): the answer has many valid forms, so comparing against
# a brute force is wrong. The checker is called as
#     check.exe <input-file> <output-file>
# and must exit 0 when the produced answer is valid, non-zero otherwise
# (printing the reason on stdout or stderr). No brute force is needed.
#
# Convention:
#   gen.cpp    reads one integer seed from argv[1], prints a test case to stdout
#   brute.cpp  reads the test case from stdin, prints the answer to stdout
#   sol.cpp    same interface as brute.cpp, this is the program under test
#
# Everything lands in stress\stress_out (D:\code\stress\stress_out):
#   sol_<hash>.exe / brute_<hash>.exe / gen_<hash>.exe   per-source binaries,
#       so switching -Sol can never reuse a binary built from another file
#   in.txt / sol.out / brute.out                          scratch files
#   fail_<case>_<seed>.{in,out,brute.out}                 a mismatch
#   keep\<case>_<seed>\{in,sol,brute}.txt                 with -Keep
#   logs\<timestamp>_<sol>.log + latest.log                 full transcript
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
    [string]$Check = '',
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

# output goes to <script folder>\stress_out = D:\code\stress\stress_out
if (-not $OutDir) { $OutDir = Join-Path $PSScriptRoot 'stress_out' }
if (-not (Test-Path -LiteralPath $OutDir)) {
    New-Item -ItemType Directory -Path $OutDir -Force | Out-Null
}
$OutDir = (Resolve-Path -LiteralPath $OutDir).Path

# ---------------------------------------------------------------- logging
$logDir = Join-Path $OutDir 'logs'
if (-not (Test-Path -LiteralPath $logDir)) { New-Item -ItemType Directory -Path $logDir -Force | Out-Null }
$solTag = if ($Sol) { [IO.Path]::GetFileNameWithoutExtension($Sol) } else { 'sol' }
$LogPath = Join-Path $logDir ('{0}_{1}.log' -f (Get-Date -Format 'yyyyMMdd_HHmmss'), $solTag)
$LatestPath = Join-Path $OutDir 'latest.log'
Set-Content -LiteralPath $LatestPath -Value '' -Encoding UTF8

function Write-Log([string]$text, [string]$color = '') {
    if ($color) { Write-Host $text -ForegroundColor $color } else { Write-Host $text }
    $line = $text -replace '\r', ''
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
    Add-Content -LiteralPath $LatestPath -Value $line -Encoding UTF8
}

function Die([string]$msg) {
    Write-Log "[stress] $msg" 'Red'
    Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
    exit 2
}

if ($N -lt 1) { Die '-N must be >= 1' }

# "-Sol a" is accepted as a shorthand for "a.cpp".
function Add-CppExt([string]$p) {
    if ((Test-Path -LiteralPath $p) -or [IO.Path]::HasExtension($p)) { return $p }
    $q = $p + '.cpp'
    if (Test-Path -LiteralPath $q) { return $q }
    return $p
}
$Sol = Add-CppExt $Sol
if (-not $Check) { $Brute = Add-CppExt $Brute }
$Gen = Add-CppExt $Gen
if ($Check) { $Check = Add-CppExt $Check }

$need = @(@($Sol, 'sol'), @($Gen, 'gen'))
if ($Check) { $need += , @($Check, 'check') } else { $need += , @($Brute, 'brute') }
foreach ($pair in $need) {
    if (-not (Test-Path -LiteralPath $pair[0])) {
        Die ("{0} not found: {1}" -f $pair[1], $pair[0])
    }
}
$SolSrc = (Resolve-Path -LiteralPath $Sol).Path
$GenSrc = (Resolve-Path -LiteralPath $Gen).Path
$BruteSrc = if ($Check) { $null } else { (Resolve-Path -LiteralPath $Brute).Path }
$CheckSrc = if ($Check) { (Resolve-Path -LiteralPath $Check).Path } else { $null }

$CXX = 'clang++'
if (-not (Get-Command $CXX -ErrorAction SilentlyContinue)) { $CXX = 'g++' }
if (-not (Get-Command $CXX -ErrorAction SilentlyContinue)) { Die 'no C++ compiler found (clang++ / g++)' }

# each source gets its own binary name: sol_<hash12>.exe, brute_<hash>.exe, ...
# A single shared sol.exe would be silently reused when you switch -Sol to a
# different file whose timestamp is older than the last build, and you would
# be testing the wrong program.
function Get-SourceKey([string]$src) {
    $sha = [System.Security.Cryptography.SHA1]::Create()
    try { $bytes = $sha.ComputeHash([Text.Encoding]::UTF8.GetBytes($src.ToLower())) }
    finally { $sha.Dispose() }
    (($bytes | ForEach-Object { $_.ToString('x2') }) -join '').Substring(0, 12)
}

function Build([string]$src, [string]$tag) {
    $exe = Join-Path $OutDir ('{0}_{1}.exe' -f $tag, (Get-SourceKey $src))
    if ((Test-Path -LiteralPath $exe) -and
        ((Get-Item -LiteralPath $exe).LastWriteTime -ge (Get-Item -LiteralPath $src).LastWriteTime)) {
        return $exe
    }
    Write-Log ("[stress] building {0} ..." -f (Split-Path $src -Leaf)) 'DarkGray'
    $sw = [Diagnostics.Stopwatch]::StartNew()
    & $CXX -std=c++20 -O2 $src -o $exe
    $code = $LASTEXITCODE
    $sw.Stop()
    if ($code -ne 0) { Die ("compile failed: {0}" -f $src) }
    Write-Log ("[stress] built {0} in {1:N1}s" -f (Split-Path $exe -Leaf), $sw.Elapsed.TotalSeconds) 'DarkGray'
    return $exe
}

$SolExe = Build $SolSrc 'sol'
$GenExe = Build $GenSrc 'gen'
$BruteExe = if ($BruteSrc) { Build $BruteSrc 'brute' } else { $null }
$CheckExe = if ($CheckSrc) { Build $CheckSrc 'check' } else { $null }

$InFile = Join-Path $OutDir 'in.txt'
$SolOut = Join-Path $OutDir 'sol.out'
$BruteOut = Join-Path $OutDir 'brute.out'
$SolErr = Join-Path $OutDir 'sol.err'
$BruteErr = Join-Path $OutDir 'brute.err'
$GenErr = Join-Path $OutDir 'gen.err'
$CheckOut = Join-Path $OutDir 'check.out'
$CheckErr = Join-Path $OutDir 'check.err'
$EmptyIn = Join-Path $OutDir 'empty.in'
Set-Content -LiteralPath $EmptyIn -Value '' -Encoding ASCII

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
    foreach ($l in $c) { Write-Log ('    ' + $l) 'DarkYellow' }
}

if ($Seed -gt 0) { $base = $Seed } else { $base = Get-Random -Minimum 1 -Maximum 2000000000 }

Write-Log ("[stress] sol   = {0}" -f $SolSrc) 'Cyan'
if ($Check) { Write-Log ("[stress] check = {0}" -f $CheckSrc) 'Cyan' }
else { Write-Log ("[stress] brute = {0}" -f $BruteSrc) 'Cyan' }
Write-Log ("[stress] gen   = {0}" -f $GenSrc) 'Cyan'
Write-Log ("[stress] out   = {0}" -f $OutDir) 'DarkGray'
$mode = if ($Check) { 'check' } elseif ($Strict) { 'byte' } else { 'token' }
Write-Log ("[stress] cases={0}  timeout={1}ms  base-seed={2}  mode={3}" -f $N, $TimeoutMs, $base, $mode) 'Cyan'

$total = [Diagnostics.Stopwatch]::StartNew()
$lastTick = 0

for ($i = 1; $i -le $N; $i++) {
    $seed = $base + $i - 1

    $r = Invoke-Program $GenExe $EmptyIn $InFile $GenErr 20000 ([string]$seed)
    if ($r -ne 'OK') {
        Write-Log ("[stress] generator failed ({0}) on seed {1}" -f $r, $seed) 'Red'
        Show-Head $GenErr 10
        Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
        exit 1
    }
    if ((Get-Item -LiteralPath $InFile).Length -eq 0) {
        Write-Log ("[stress] generator produced empty output on seed {0}" -f $seed) 'Red'
        Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
        exit 1
    }

    $solResult = Invoke-Program $SolExe $InFile $SolOut $SolErr $TimeoutMs
    if ($solResult -ne 'OK') {
        $bad = Join-Path $OutDir ("fail_{0}_{1}.in" -f $i, $seed)
        Copy-Item -LiteralPath $InFile -Destination $bad -Force
        Write-Log ""
        Write-Log ("[stress] case #{0} (seed {1}): solution {2}" -f $i, $seed, $solResult) 'Red'
        Write-Log ("[stress] input saved to {0}" -f $bad) 'Red'
        Show-Head $SolErr 8
        Write-Log ("[stress] reproduce: .\stress.ps1 -Seed {0} -N 1" -f $seed) 'Yellow'
        Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
        exit 1
    }

    if ($Check) {
        # checker mode: the answer has many valid forms, so validate it instead
        # of comparing with a brute force.  check.exe <input> <output>
        $checkResult = Invoke-Program $CheckExe $EmptyIn $CheckOut $CheckErr 20000 `
            ('"{0}" "{1}"' -f $InFile, $SolOut)
        if ($checkResult -ne 'OK') {
            $badIn = Join-Path $OutDir ("fail_{0}_{1}.in" -f $i, $seed)
            $badOut = Join-Path $OutDir ("fail_{0}_{1}.out" -f $i, $seed)
            Copy-Item -LiteralPath $InFile -Destination $badIn -Force
            Copy-Item -LiteralPath $SolOut -Destination $badOut -Force
            Write-Log ""
            Write-Log ("[stress] INVALID ANSWER on case #{0} (seed {1})" -f $i, $seed) 'Red'
            $msg = @(Get-Content -LiteralPath $CheckOut -TotalCount 6)
            $msg += @(Get-Content -LiteralPath $CheckErr -TotalCount 6)
            foreach ($m in $msg) { Write-Log ("  checker: {0}" -f $m) 'Yellow' }
            Write-Log ("  input  : {0}" -f $badIn) 'Red'
            Write-Log ("  output : {0}" -f $badOut) 'Red'
            Write-Log ("  reproduce: .\stress.ps1 -Seed {0} -N 1" -f $seed) 'Yellow'
            Write-Log ("  log: {0}" -f $LogPath) 'DarkGray'
            exit 1
        }
        if ($Keep) {
            $kd = Join-Path $OutDir ('keep\' + ("{0}_{1}" -f $i, $seed))
            New-Item -ItemType Directory -Path $kd -Force | Out-Null
            Copy-Item -LiteralPath $InFile -Destination (Join-Path $kd 'in.txt') -Force
            Copy-Item -LiteralPath $SolOut -Destination (Join-Path $kd 'sol.txt') -Force
        }
        if ($N -ge 20) {
            $tick = [int](10.0 * $i / $N)
            if ($tick -ne $lastTick) {
                $lastTick = $tick
                Write-Host ("  {0,3}%" -f ($tick * 10)) -NoNewline
                Write-Host ("  ({0}/{1})" -f $i, $N) -ForegroundColor DarkGray
            }
        }
        continue
    }

    $bruteResult = Invoke-Program $BruteExe $InFile $BruteOut $BruteErr ($TimeoutMs * 3)
    if ($bruteResult -ne 'OK') {
        Write-Log ("[stress] case #{0}: brute {1} - brute is too slow or buggy, raise -TimeoutMs" -f $i, $bruteResult) 'Red'
        Show-Head $BruteErr 8
        Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
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

        Write-Log ""
        Write-Log ("[stress] WRONG ANSWER on case #{0} (seed {1})" -f $i, $seed) 'Red'
        Write-Log ("  first different token: #{0} (1-based {1})" -f $pos, ($pos + 1)) 'Yellow'
        $from = [Math]::Max(0, $pos - 4)
        $to = $pos + 5
        $segA = for ($k = $from; $k -lt [Math]::Min($to, $tokA.Count); $k++) { $tokA[$k] }
        $segB = for ($k = $from; $k -lt [Math]::Min($to, $tokB.Count); $k++) { $tokB[$k] }
        Write-Log ("  sol  : {0}" -f (@($segA) -join ' ')) 'Yellow'
        Write-Log ("  brute: {0}" -f (@($segB) -join ' ')) 'Yellow'
        Write-Log ("  tokens: sol={0}  brute={1}" -f $tokA.Count, $tokB.Count) 'DarkGray'
        Write-Log ("  input  : {0}" -f $badIn) 'Red'
        Write-Log ("  sol out: {0}" -f $badOut) 'Red'
        Write-Log ("  brute  : {0}" -f $badBr) 'Red'
        Write-Log ("  reproduce: .\stress.ps1 -Seed {0} -N 1" -f $seed) 'Yellow'
        Write-Log ("  log: {0}" -f $LogPath) 'DarkGray'
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
Write-Log ""
Write-Log ("[stress] all {0} cases passed in {1:N1}s" -f $N, $total.Elapsed.TotalSeconds) 'Green'
Write-Log ("[stress] log: {0}" -f $LogPath) 'DarkGray'
Write-Log ("[stress] latest: {0}" -f $LatestPath) 'DarkGray'
exit 0
