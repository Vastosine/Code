import random, subprocess, os, sys, itertools

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_g.exe"
r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL"); print(r.stderr.decode()[:400]); sys.exit(1)

def bad(x, y, k, op):          # x != y
    if op == 0: return x == k*y or y == k*x
    return (x // y == k) or (y // x == k)

def chrom(a, k):
    n = len(a)
    adj = [[bad(a[i], a[j], k, 1) for j in range(n)] for i in range(n)]
    for t in range(1, n + 1):
        col = [-1]*n
        def go(u):
            if u == n: return True
            for c in range(t):
                if all(not (adj[u][v] and col[v] == c) for v in range(u)):
                    col[u] = c
                    if go(u+1): return True
                    col[u] = -1
            return False
        if go(0): return t
    return n

def run(a, k):
    data = f"{len(a)} {k} 1\n" + " ".join(map(str, a)) + "\n"
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    it = iter(out); m = int(next(it)); gs = []
    for _ in range(m):
        c = int(next(it)); gs.append([int(next(it)) for _ in range(c)])
    return gs

rnd = random.Random(99991)
cnt = {2: 0, 3: 0}
bad3 = 0
shown = 0
for tc in range(6000):
    k = rnd.choice([2, 2, 3])
    n = rnd.randint(4, 13)
    hi = rnd.choice([60, 120, 300])
    a = sorted(rnd.sample(range(1, hi + 1), n))
    chi = chrom(a, k)
    if chi not in (2, 3): continue
    cnt[chi] += 1
    gs = run(a, k)
    flat = sorted(v for g in gs for v in g)
    valid = flat == a and all(not bad(x, y, k, 1) for g in gs for x, y in itertools.combinations(g, 2))
    if not valid or len(gs) != chi:
        bad3 += 1
        if shown < 10:
            shown += 1
            print(f"k={k} a={a}  chi={chi}  got m={len(gs)} valid={valid}  groups={gs}")

print(f"\nchi=2 cases: {cnt[2]}    chi=3 cases: {cnt[3]}    mismatches: {bad3}")
os.remove(EXE)
