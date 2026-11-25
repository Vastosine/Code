import random, sys

def level(a, k):
    p, t = 0, 1
    while t * k <= a:
        t *= k
        p += 1
    return p

rnd = random.Random(31415)
bad = [0, 0]
trials = 0
for tc in range(4000):
    op = tc & 1
    k = rnd.choice([2, 3, 4, 5, 7, 13, 100, 10**4, 10**9])
    n = rnd.randint(2, 15)
    top = min(10**18, k ** rnd.randint(1, 6) * 3)
    pool = set()
    while len(pool) < n and len(pool) < top:
        pool.add(rnd.randint(1, max(2, top)))
    a = sorted(pool)
    if len(a) < 2:
        continue
    trials += 1
    L = [level(x, k) for x in a]
    mod = 2 if op == 0 else 3
    for i in range(len(a)):
        for j in range(i + 1, len(a)):
            x, y = a[i], a[j]
            hit = (y == k * x) if op == 0 else (y // x == k)
            if hit and L[i] % mod == L[j] % mod:
                bad[op] += 1
                if sum(bad) <= 5:
                    print(f"COUNTEREXAMPLE op={op} k={k} {x}(L={L[i]}) {y}(L={L[j]}) dL={L[j]-L[i]}")
                break
        else:
            continue
        break

print(f"{trials} cases:  L mod 2 broken {bad[0]} times (op=0)   L mod 3 broken {bad[1]} times (op=1)")
print()
a = [4, 8, 11, 16, 32]; k = 2
print("sample-2 C5 (k=2):", [(x, level(x, k), level(x, k) % 3) for x in a])
