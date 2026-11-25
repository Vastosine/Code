import random, subprocess, os, sys, itertools

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_w.exe"
r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL"); print(r.stderr.decode()[:500]); sys.exit(1)

def bad(x, y, k, op):
    if x == y: return False
    if op == 0: return x == k * y or y == k * x
    return (x // y == k) or (y // x == k)   # python ints: no overflow

def valid(groups, a, k, op):
    if sorted(v for g in groups for v in g) != sorted(a): return False, "not a partition"
    for g in groups:
        for x, y in itertools.combinations(g, 2):
            if bad(x, y, k, op): return False, f"pair {x},{y} together"
    return True, ""

def chrom(a, k, op):
    n = len(a)
    adj = [[bad(a[i], a[j], k, op) for j in range(n)] for i in range(n)]
    for t in range(1, n + 1):
        col = [-1] * n
        def go(u):
            if u == n: return True
            for c in range(t):
                if all(not (adj[u][v] and col[v] == c) for v in range(u)):
                    col[u] = c
                    if go(u + 1): return True
                    col[u] = -1
            return False
        if go(0): return t
    return n

def run(a, k, op):
    data = f"{len(a)} {k} {op}\n" + " ".join(map(str, a)) + "\n"
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    it = iter(out); m = int(next(it)); gs = []
    for _ in range(m):
        c = int(next(it)); gs.append([int(next(it)) for _ in range(c)])
    return gs

bad_n = 0; shown = 0
rnd = random.Random(777)

# 1) the two minimal counterexamples from the OLD version
for a, k, op, want in ([2, 5], 2, 0, 1), ([2, 3, 4, 8], 2, 1, 2):
    gs = run(a, k, op)
    ok, err = valid(gs, a, k, op)
    flag = "OK" if ok and len(gs) == want else "**WRONG**"
    print(f"op={op} k={k} a={a}  got m={len(gs)} want {want}  valid={ok}  {flag}")

# 2) random, tiny values
for tc in range(2500):
    op = tc & 1; k = 2 + rnd.randrange(4); m = rnd.randint(1, 8)
    hi = rnd.choice([10, 30, 100])
    a = sorted(rnd.sample(range(1, hi + 1), min(m, hi)))
    gs = run(a, k, op); ok, err = valid(gs, a, k, op); opt = chrom(a, k, op)
    if not ok or len(gs) != opt:
        bad_n += 1
        if shown < 8:
            shown += 1
            print(f"SMALL op={op} k={k} a={a} got m={len(gs)} opt={opt} valid={ok} {err}")

# 3) random, HUGE values (a_i near 1e18) -- overflow territory
for tc in range(1200):
    op = tc & 1; k = rnd.choice([2, 3, 10, 1000, 10**9])
    n = rnd.randint(1, 6); a = set()
    while len(a) < n:
        base = rnd.choice([1, 2, 10**6, 10**9, 10**12, 10**15, 10**18 // (k + 1)])
        a.add(max(1, min(10**18, base * rnd.choice([1, 1, 1, k, k + 1, 2 * k]))))
    a = sorted(a)
    gs = run(a, k, op); ok, err = valid(gs, a, k, op); opt = chrom(a, k, op)
    if not ok or len(gs) != opt:
        bad_n += 1
        if shown < 16:
            shown += 1
            print(f"BIG   op={op} k={k} a={a} got m={len(gs)} opt={opt} valid={ok} {err}")

print(f"\ntotal wrong: {bad_n}   (2500 small + 1200 huge + 2 hand cases)")
os.remove(EXE)
