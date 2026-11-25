import random, subprocess, os, sys

SRC = r"D:\code\OI\contests\others\CSP43\5.cpp"
G   = r"D:\programs\OI\mingw64\bin\g++.exe"
W   = r"D:\code\stress"

body = open(SRC, encoding="utf-8-sig").read()
assert "__builtin_popcountll" in body

variants = {
    "ll":  body,
    "int": body.replace("__builtin_popcountll", "__builtin_popcount"),
}
for name, code in variants.items():
    p = os.path.join(W, f"_t5_{name}.cpp")
    open(p, "w", encoding="utf-8", newline="\n").write(code)
    r = subprocess.run([G, "-std=c++17", "-O2", "-o", os.path.join(W, f"_t5_{name}.exe"), p],
                       capture_output=True)
    if r.returncode != 0:
        print("COMPILE FAIL", name, r.stderr.decode()[:400]); sys.exit(1)

def gen(n, m, k, q, seed):
    rnd = random.Random(seed)
    lines = [f"{n} {m} {k} {q}"]
    lines.append("".join(rnd.choice("01") for _ in range(n)))
    lines.append(" ".join(str(rnd.randint(1, m)) for _ in range(n)))
    for v in range(2, n + 1):
        u = rnd.randint(1, v - 1)
        lines.append(f"{u} {v} {rnd.randint(1, 10**6)}")
    for _ in range(q):
        lines.append(str(rnd.randint(1, n)))
    return "\n".join(lines) + "\n"

def run(exe, data):
    r = subprocess.run([os.path.join(W, exe)], input=data.encode(), capture_output=True)
    return r.stdout.decode().split()

cases = [
    ("m=30", gen(150, 30, 4, 40, 1)),
    ("m=33", gen(150, 33, 4, 40, 2)),
    ("m=40", gen(150, 40, 4, 40, 3)),
    ("m=40 b", gen(120, 40, 2, 30, 4)),
]
for name, data in cases:
    a = run("_t5_ll.exe", data)
    b = run("_t5_int.exe", data)
    diff = sum(1 for x, y in zip(a, b) if x != y)
    print(f"{name:8} lines={len(a):4}  differing lines={diff:4}   "
          + ("SAME" if diff == 0 else "**DIFFERENT**"))

for f in os.listdir(W):
    if f.startswith("_t5_") and (f.endswith(".exe") or f.endswith(".cpp")):
        os.remove(os.path.join(W, f))
