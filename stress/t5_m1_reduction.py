import random, subprocess, os, sys
from collections import deque

G = r"D:\programs\OI\mingw64\bin\g++.exe"
W = r"D:\code\stress"
SRC = r"D:\code\OI\contests\others\CSP43\5.cpp"

exe = os.path.join(W, "_t5_verify.exe")
r = subprocess.run([G, "-std=c++17", "-O2", "-o", exe, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL", r.stderr.decode()[:300]); sys.exit(1)

def gen(n, k, seed):
    rnd = random.Random(seed)
    s = [rnd.choice("01") for _ in range(n)]
    col = [1] * n                      # m = 1
    edges = []
    for v in range(2, n + 1):
        u = rnd.randint(1, v - 1)
        edges.append((u, v, rnd.randint(1, 10**6)))
    q = 0
    lines = [f"{n} 1 {k} {q}", "".join(s), " ".join(map(str, col))]
    lines += [f"{u} {v} {w}" for u, v, w in edges]
    return "\n".join(lines) + "\n", s, edges

def brute(n, k, s, edges):
    adj = [[] for _ in range(n + 1)]
    for u, v, w in edges:
        adj[u].append((v, w)); adj[v].append((u, w))
    INF = 1
    dep = [0] * (n + 1); dis = [0] * (n + 1)
    par = [0] * (n + 1); order = [1]; par[1] = 0
    seen = [False] * (n + 1); seen[1] = True
    for u in order:
        for v, w in adj[u]:
            if not seen[v]:
                seen[v] = True; par[v] = u
                dep[v] = dep[u] + 1; dis[v] = dis[u] + w
                order.append(v)
    # LCA by parent walk (n is small)
    def lca(a, b):
        while dep[a] > dep[b]: a = par[a]
        while dep[b] > dep[a]: b = par[b]
        while a != b: a = par[a]; b = par[b]
        return a
    cnt = 0
    for u in range(1, n + 1):
        if s[u - 1] != '1': continue
        for v in range(u, n + 1):
            if s[v - 1] != '1': continue
            x = lca(u, v)
            d = dis[u] + dis[v] - 2 * dis[x]
            if d % k: continue
            if (dep[u] ^ dep[v]) & 1: continue     # parity must match
            cnt += 1
    return cnt

bad = 0
for t in range(40):
    n = random.Random(t).randint(2, 60)
    k = random.Random(t + 999).randint(2, 4)
    data, s, edges = gen(n, k, t)
    got = int(subprocess.run([exe], input=data.encode(), capture_output=True).stdout.split()[0])
    want = brute(n, k, s, edges)
    if got != want:
        bad += 1
        print(f"MISMATCH n={n} k={k}  his={got}  reduction={want}")
print(("ALL MATCH" if bad == 0 else f"{bad} mismatches") + "  (40 random m=1 trees, reduction vs his O(n^2) code)")
os.remove(exe)
