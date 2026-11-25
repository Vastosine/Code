import subprocess, os, time, sys

G   = r"D:\programs\OI\mingw64\bin\g++.exe"
SRC = r"D:\code\OI\contests\others\CSP43\4.cpp"
EXE = r"D:\code\stress\_t4_t.exe"

r = subprocess.run([G, "-std=c++17", "-O2", "-o", EXE, SRC], capture_output=True)
if r.returncode:
    print("COMPILE FAIL"); print(r.stderr.decode()[:400]); sys.exit(1)

def dense(N, k=2):
    # a = N .. 3N-1  (dense window -> ratio in [k, k+1) happens a lot)
    a = list(range(N, 3 * N))
    return a

print("k=2, a = [N, 3N)  -- dense, maximizes the number of conflict edges")
print(f"{'n':>7} {'edges(est)':>12} {'time':>9}   m")
for N in (2500, 5000, 10000, 20000):
    a = dense(N)
    n = len(a)
    data = f"{n} 2 1\n" + " ".join(map(str, a)) + "\n"
    t0 = time.perf_counter()
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    dt = time.perf_counter() - t0
    m = out[0] if out else "?"
    est = 0.156 * n * n
    print(f"{n:7d} {est:12.3e} {dt:8.3f}s   m={m}")

print()
print("op=0 on the same dense data (should be fast, O(n log n)):")
for N in (20000, 200000):
    a = list(range(N, 3 * N)); n = len(a)
    data = f"{n} 2 0\n" + " ".join(map(str, a)) + "\n"
    t0 = time.perf_counter()
    out = subprocess.run([EXE], input=data.encode(), capture_output=True).stdout.decode().split()
    dt = time.perf_counter() - t0
    print(f"  n={n:7d}  {dt:8.3f}s   m={out[0] if out else '?'}")

os.remove(EXE)
