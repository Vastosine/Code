import random, subprocess, os, sys, itertools

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_g2.exe"
r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL"); print(r.stderr.decode()[:400]); sys.exit(1)

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
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    it = iter(out); m = int(next(it)); gs = []
    for _ in range(m):
        c = int(next(it)); gs.append([int(next(it)) for _ in range(c)])
    return gs

rnd = random.Random(4242)
# base chirality-3 patterns, found by scaling the sample-2 C5 and by search
bases = {2: [[4, 8, 11, 16, 32]]}
for k in (3, 4, 5):
    found = []
    for _ in range(200000):
        n = rnd.randint(5, 7)
        a = sorted(rnd.sample(range(1, 150), n))
        if chrom(a, k) == 3:
            found.append(a)
            if len(found) >= 3: break
    bases[k] = found
    print(f"k={k}: found {len(found)} chi=3 bases {found}")

total = ok3 = badn = 0
for k, bs in bases.items():
    for base in bs:
        for t in (1, 2, 3, 5, 7, 11, 13, 101, 1000, 999983):
            scaled = [x * t for x in base]
            if max(scaled) > 10**18: continue
            for extra in range(4):
                pool = set(scaled)
                tries = 0
                while len(pool) < len(scaled) + extra and tries < 200:
                    tries += 1
                    v = rnd.choice(scaled) * rnd.choice([1, 1, 2, 3])
                    if v <= 10**18: pool.add(v)
                a = sorted(pool)
                if len(a) > 12: continue
                if chrom(a, k) != 3: continue     # C5 guarantees >=3; keep only exactly 3
                total += 1
                gs = run(a, k)
                flat = sorted(v for g in gs for v in g)
                valid = flat == a and all(not bad(x, y, k) for g in gs for x, y in itertools.combinations(g, 2))
                if valid and len(gs) == 3:
                    ok3 += 1
                else:
                    badn += 1
                    if badn <= 10:
                        print(f"k={k} a={a} chi=3 got m={len(gs)} valid={valid} groups={gs}")

print(f"\nchi=3 targeted cases: {total}   greedy gave exactly 3 & valid: {ok3}   wrong: {badn}")
os.remove(EXE)
