# fetch_luogu_ac.ps1 - build { pid -> first-AC date } from the Luogu record list
#
# The record list endpoint is login-only. It needs BOTH `_uid` (single underscore)
# and `__client_id` (double underscore); all earlier 401s were caused by sending
# __uid or only one of the pair.
#
# perPage is fixed at 20 and pageSize is ignored, so the whole list is walked
# page by page (currently 3678 records -> 184 pages).
#
# status 12 = Accepted. Everything else (14 = partial, 2 = CE, ...) is ignored.
#
# Output: plan\cache\luogu_ac.json
#   { "generated": "...", "records": 3678, "pids": 812, "ac": { "P1002": "2021-07-22", ... } }
#
# Usage: .\fetch_luogu_ac.ps1 [-Uid 439583] [-DelayMs 300] [-Force]

param(
    [int]$Uid = 439583,
    [int]$DelayMs = 300,
    [string]$CookieFile = 'D:\code\plan\luogu_cookies.txt',
    [string]$Out = 'D:\code\plan\cache\luogu_ac.json',
    [switch]$Force
)

$ErrorActionPreference = 'Stop'
# PowerShell variable names are case-INsensitive: $AC and $ac are the same variable.
# Keep the status constant and the map clearly apart.
$AcceptedStatus = 12

if ((Test-Path $Out) -and -not $Force) {
    $age = ((Get-Date) - (Get-Item $Out).LastWriteTime).TotalHours
    if ($age -lt 12) { "cache is fresh ({0:N1} h old): $Out" -f $age; return }
}

if (-not (Test-Path $CookieFile)) { throw "missing cookie file: $CookieFile" }
$ck = (Get-Content $CookieFile | Where-Object { $_ -and -not $_.StartsWith('#') } | ForEach-Object {
    $p = $_ -split "`t"
    "$($p[5])=$($p[6])"
}) -join '; '
if (-not $ck) { throw 'no cookies parsed from ' + $CookieFile }

$tmp = Join-Path $env:TEMP 'lgpage.json'
$acMap = @{}
$lastMap = @{}
$page = 1
$total = -1
$fetched = 0

while ($true) {
    $url = "https://www.luogu.com.cn/record/list?user=$Uid&page=$page&_contentOnly=1"
    $got = $null
    for ($try = 1; $try -le 4; $try++) {
        # 2026-11-27: `-b $CookieFile` now 401s -- curl skips __client_id because its
        # cookie-file expiry (1795695010) is in the past, while the server still accepts
        # the value. Send the parsed pair as an explicit header instead.
        curl.exe -s --compressed -H "Cookie: $ck" -H "x-lentille-request: content-only" $url -o $tmp
        try {
            $j = Get-Content $tmp -Raw -Encoding UTF8 | ConvertFrom-Json
            if ($j.data.records -and $j.data.records.result) { $got = $j.data.records; break }
        } catch { }
        Start-Sleep -Seconds 2
    }
    if (-not $got) { Write-Host "page $page FAILED after 4 tries - stopping at $fetched records"; break }

    if ($total -lt 0) { $total = $got.count; Write-Host "total records: $total" }
    foreach ($rec in $got.result) {
        $fetched++
        $probId = $rec.problem.pid
        $t = [int64]$rec.submitTime
        # last submission of ANY status: this is what the .cpp on disk represents
        # (the file is the LAST version written, not the first-AC version)
        if (-not $lastMap.ContainsKey($probId) -or $t -gt $lastMap[$probId]) { $lastMap[$probId] = $t }
        if ($rec.status -ne $AcceptedStatus) { continue }
        if (-not $acMap.ContainsKey($probId) -or $t -lt $acMap[$probId]) { $acMap[$probId] = $t }
    }
    if ($fetched -ge $total) { break }
    if ($got.result.Count -lt $got.perPage) { break }
    if ($page -ge 400) { break }
    $page++
    if ($page % 20 -eq 0) { Write-Host "  page $page / $([math]::Ceiling($total / 20.0))  ($fetched records)" }
    Start-Sleep -Milliseconds $DelayMs
}

# 2026-11-27: never overwrite a good cache with a failed crawl. A 401 on page 1 used to
# fall through and write {records:0, firstAc:{}} over 632 AC records.
if ($fetched -eq 0) { throw "page 1 failed (no records parsed) - cache left untouched: $Out" }
$partial = ($total -gt 0 -and $fetched -lt $total)

# unix -> yyyy-MM-dd in +08:00
function ToDate([int64]$t) {
    [DateTimeOffset]::FromUnixTimeSeconds($t).ToOffset([TimeSpan]::FromHours(8)).ToString('yyyy-MM-dd')
}
$acDate = @{}
foreach ($k in $acMap.Keys) { $acDate[$k] = ToDate $acMap[$k] }
$lastDate = @{}
foreach ($k in $lastMap.Keys) { $lastDate[$k] = ToDate $lastMap[$k] }

# A partial crawl only knows the newest N pages, so pids older than the cut-off would
# disappear. Keep whatever the previous cache had for pids this run did not see.
$kept = 0
if (Test-Path $Out) {
    try { $old = Get-Content $Out -Raw -Encoding UTF8 | ConvertFrom-Json } catch { $old = $null }
    if ($old) {
        foreach ($k in $old.firstAc.PSObject.Properties.Name) {
            if (-not $acDate.ContainsKey($k)) { $acDate[$k] = $old.firstAc.$k; $kept++ }
        }
        foreach ($k in $old.lastSubmit.PSObject.Properties.Name) {
            if (-not $lastDate.ContainsKey($k)) { $lastDate[$k] = $old.lastSubmit.$k }
        }
    }
}

$dir = Split-Path $Out -Parent
if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
$payload = [pscustomobject]@{
    generated  = (Get-Date).ToString('yyyy-MM-dd HH:mm:ss')
    records    = $fetched
    total      = $total
    partial    = $partial
    keptFromOld = $kept
    pids       = $lastDate.Count
    acPids     = $acDate.Count
    firstAc    = $acDate
    lastSubmit = $lastDate
}
[IO.File]::WriteAllText($Out, ($payload | ConvertTo-Json -Depth 3 -Compress), (New-Object System.Text.UTF8Encoding($false)))

''
'fetched {0} records, {1} pids total, {2} ever AC -> {3}' -f $fetched, $lastDate.Count, $acDate.Count, $Out
