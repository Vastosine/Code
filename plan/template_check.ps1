# Check the competitive-programming template by instantiating every helper and compiling.
# Usage: powershell -NoProfile -File plan\template_check.ps1 [-Template <path>]
param(
    [string]$Template = "D:\code\template.cpp",
    [string]$Compiler = "g++"
)
$ErrorActionPreference = "Stop"

if (-not (Test-Path -LiteralPath $Template)) {
    Write-Host "FAIL: template not found: $Template" -ForegroundColor Red
    exit 1
}

$tmp = Join-Path $env:TEMP ("tmplcheck_" + [guid]::NewGuid().ToString("N").Substring(0, 8))
New-Item -ItemType Directory -Force -Path $tmp | Out-Null
$src = Join-Path $tmp "check.cpp"

# Keep everything before "auto Main" (includes + helper templates), then append a test main
# that forces instantiation of every helper.
$lines = Get-Content -LiteralPath $Template
$cut = -1
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match '^\s*auto\s+Main\s*\(') { $cut = $i; break }
}
if ($cut -lt 0) {
    Write-Host "FAIL: could not find 'auto Main(' in template" -ForegroundColor Red
    exit 1
}
$head = $lines[0..($cut - 1)]

$tail = @'
auto Main(int C = 0) {
    vi v{3, 1, 2}, w{5, 4};
    Sort(v);
    Sort(w, [] (int a, int b) { return a > b; });
    assign(3, v, w);
    vector<pii> p{{1, 2}, {3, 4}};
    Sort(p, [] (pii a, pii b) { return a.first < b.first; });
    cout << v << '\n' << w << '\n';
    string s;
    cin >> s;
    cout << s << '\n' << p[0].first << '\n';
    ll big = INF + NEG;
    cout << big << '\n';
    return 0;
}

int main() {
    auto ans = Main(0);
    cout << ans << '\n';
    return 0;
}
'@ -split "`r?`n"

$all = @($head) + @($tail)
Set-Content -LiteralPath $src -Value $all -Encoding ascii

$exe = Join-Path $tmp "check.exe"
$out = & $Compiler -std=c++17 -O2 -o $exe $src 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL: template does not compile when all helpers are used" -ForegroundColor Red
    $out | Select-Object -First 15 | ForEach-Object { Write-Host $_ }
    exit 1
}
Write-Host "PASS: template compiles (Sort / assign / vector IO / string / pair / INF all instantiated)" -ForegroundColor Green
Remove-Item -Recurse -Force $tmp
