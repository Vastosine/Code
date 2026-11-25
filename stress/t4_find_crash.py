import random, subprocess, os, sys, itertools

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_g3.exe"
r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL"); sys.exit(1)

def bad(x, y, k):
    if x == y: return False
    return (x // y == k) or (y // x == k)

def chrom(a, k):
    n = len(a)
    adj = [[bad(a[i], a[j], k) for j in range(n)] for i in range(n)]
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
    p = subprocess.run([EXE], input=data.encode(), capture_output=True)
    toks = p.stdout.decode().split()
    if not toks:
        return None, p.returncode, p.stderr.decode()[:200]
    it = iter(toks); m = int(next(it)); gs = []
    for _ in range(m):
        c = int(next(it)); gs.append([int(next(it)) for _ in range(c)])
    return gs, p.returncode, ""

rnd = random.Random(4242)
crashes = 0
chi3 = 0
wrong = 0
base = [4, 8, 11, 16, 32]
cases = []
for t in (1, 2, 3, 5, 7, 11, 101, 1000, 999983):
    scaled = [x * t for x in base]
    cases.append(scaled)
    for extra in range(1, 5):
        pool = set(scaled)
        tries = 0
        while len(pool) < len(scaled) + extra and tries < 500:
            tries += 1
            v = rnd.choice(scaled) * rnd.choice([1, 2, 3])
            if v <= 10**18: pool.add(v)
        cases.append(sorted(pool))
# random chi=3 candidates from a wide k=2 range too
for _ in range(400):
    a = sorted(rnd.sample(range(1, 1000), rnd.randint(5, 11)))
    if chrom(sorted(a), 2) == 3: cases.append(a)

for a in cases:
    gs, rc, err = run(a, 2)
    if gs is None:
        crashes += 1
        if crashes <= 8:
            print(f"CRASH rc={rc} a={a} err={err!r}")
        continue
    chi = chrom(a, 2)
    if chi != 3: continue
    chi3 += 1
    flat = sorted(v for g in gs for v in g)
    valid = flat == a and all(not bad(x, y, 2) for g in gs for x, y in itertools.combinations(g, 2))
    if not (valid and len(gs) == 3):
        wrong += 1
        if wrong <= 8: print(f"WRONG chi=3 a={a} got m={len(gs)} valid={valid} groups={gs}")

print(f"\ncases={len(cases)} crashes={crashes} chi3={chi3} wrong={wrong}")
os.remove(EXE)
