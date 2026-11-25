import random, subprocess, os, sys, itertools, time

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_f.exe"
r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode: print("COMPILE FAIL"); print(r.stderr.decode()[:400]); sys.exit(1)

def bad(x, y, k, op):
    if x == y: return False
    if op == 0: return x == k * y or y == k * x
    return (x // y == k) or (y // x == k)

def run(a, k, op, tlimit=None):
    data = f"{len(a)} {k} {op}\n" + " ".join(map(str, a)) + "\n"
    p = subprocess.run([EXE], input=data.encode(), capture_output=True)
    toks = p.stdout.decode().split()
    if not toks: return None
    it = iter(toks); m = int(next(it)); gs = []
    for _ in range(m):
        c = int(next(it)); gs.append([int(next(it)) for _ in range(c)])
    return gs

def check(a, k, op, want=None):
    gs = run(a, k, op)
    if gs is None: return "CRASH", None
    flat = sorted(v for g in gs for v in g)
    if flat != a: return "BADPART", len(gs)
    for g in gs:
        for x, y in itertools.combinations(g, 2):
            if bad(x, y, k, op): return "CONFLICT", len(gs)
    if want is not None and len(gs) != want: return f"m={len(gs)}!= {want}", len(gs)
    return "OK", len(gs)

S2 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,17,19,20,23,25,26,28,29,31,32]
C5 = [4, 8, 11, 16, 32]

print("=== chi=3 targeted: scale the sample-2 C5 (ratio pattern is scale invariant) ===")
badn = 0; tot = 0
rnd = random.Random(5)
for t in list(range(1, 40)) + [101, 997, 10**6, 10**9, 10**12]:
    for base in (C5, C5 + [2*t], S2):
        a = sorted(set(x * t for x in base))
        if max(a) > 10**18: continue
        tot += 1
        st, m = check(a, 2, 1, 3)
        if st != "OK":
            badn += 1
            if badn <= 6: print(f"  t={t} base={'C5' if base is C5 else 'other'} {st} m={m} a={a[:6]}...")
print(f"  {tot} cases, wrong {badn}")

print("=== op=0 heavy: random multiples ===")
badn0 = tot0 = 0
for _ in range(800):
    k = rnd.choice([2, 3, 5, 10, 10**6])
    base = [rnd.randint(1, 50) for _ in range(rnd.randint(2, 8))]
    a = sorted(set(b * k ** rnd.randint(0, 3) for b in base))
    if max(a) > 10**18 or len(a) < 2: continue
    tot0 += 1
    st, m = check(a, k, 0)
    if st != "OK":
        badn0 += 1
        if badn0 <= 6: print(f"  k={k} {st} m={m} a={a}")
print(f"  {tot0} cases, wrong {badn0}")

print("=== timing: n = 5e5, op=1 and op=0 ===")
n = 500000
a = sorted(random.Random(7).sample(range(1, 4 * n), n))
for op in (1, 0):
    data = f"{n} 2 {op}\n" + " ".join(map(str, a)) + "\n"
    t0 = time.perf_counter()
    p = subprocess.run([EXE], input=data.encode(), capture_output=True)
    dt = time.perf_counter() - t0
    head = p.stdout.decode().split()[:1]
    print(f"  op={op}  {dt:6.2f}s   m={head}  rc={p.returncode}")

os.remove(EXE)
