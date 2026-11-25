import random, subprocess, os, sys, itertools

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_new.exe"

r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode:
    print("COMPILE FAIL"); print(r.stderr.decode()[:600]); sys.exit(1)

def bad_pair(x, y, k, op):
    if x == y: return False
    if op == 0: return x == k * y or y == k * x
    return x // y == k or y // x == k

def valid(groups, a, k, op):
    flat = [v for g in groups for v in g]
    if sorted(flat) != sorted(a): return False, "not a partition of the input"
    for g in groups:
        for x, y in itertools.combinations(g, 2):
            if bad_pair(x, y, k, op): return False, f"conflicting pair {x},{y} in one group"
    return True, ""

def chromatic(a, k, op):
    n = len(a)
    adj = [[bad_pair(a[i], a[j], k, op) for j in range(n)] for i in range(n)]
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

def run_case(a, k, op):
    data = f"{len(a)} {k} {op}\n" + " ".join(map(str, a)) + "\n"
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    it = iter(out)
    try:
        m = int(next(it))
        groups = []
        for _ in range(m):
            c = int(next(it))
            groups.append([int(next(it)) for _ in range(c)])
    except StopIteration:
        return None, "output too short"
    return groups, ""

rnd = random.Random(20261125)
stats = {"ok": 0, "wrong_m": 0, "invalid": 0, "crash": 0}
shown = 0
for tc in range(4000):
    op = tc & 1
    k = 2 + rnd.randrange(4)
    m = rnd.randint(2, 8)
    hi = rnd.choice([20, 40, 80, 200])
    a = rnd.sample(range(1, hi + 1), min(m, hi))
    groups, err = run_case(a, k, op)
    if groups is None:
        stats["crash"] += 1; continue
    ok, err = valid(groups, a, k, op)
    opt = chromatic(a, k, op)
    got = len(groups)
    tag = None
    if not ok:
        stats["invalid"] += 1; tag = "INVALID(" + err + ")"
    elif got != opt:
        stats["wrong_m"] += 1; tag = f"m {got} vs optimal {opt}"
    else:
        stats["ok"] += 1
    if tag and shown < 12:
        shown += 1
        print(f"op={op} k={k} a={a}  ->  {tag}   groups={groups}")

print("\n", stats, "of", 4000)
os.remove(EXE)
