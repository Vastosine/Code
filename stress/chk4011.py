import random, subprocess, sys, os
from collections import deque

def oracle(n, m, P, door, keys):
    """door[(x,y,tx,ty)] = g  (双向，g=0 墙，g>0 门)；keys[(x,y)] = bitmask"""
    start = (1, 1)
    m0 = keys.get(start, 0)
    dist = {(1, 1, m0): 0}
    dq = deque([(1, 1, m0)])
    while dq:
        x, y, mask = dq.popleft()
        d = dist[(x, y, mask)]
        if (x, y) == (n, m):
            return d
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            tx, ty = x + dx, y + dy
            if not (1 <= tx <= n and 1 <= ty <= m):
                continue
            g = door.get((x, y, tx, ty), -1)
            if g == 0:
                continue
            if g > 0 and not (mask >> (g - 1)) & 1:
                continue
            nm = mask | keys.get((tx, ty), 0)
            if (tx, ty, nm) not in dist:
                dist[(tx, ty, nm)] = d + 1
                dq.append((tx, ty, nm))
    return -1

def gen(rng):
    n = rng.randint(1, 4); m = rng.randint(1, 4)
    P = rng.randint(1, 4)
    door = {}
    # 随机墙/门
    for x in range(1, n + 1):
        for y in range(1, m + 1):
            for dx, dy in ((1, 0), (0, 1)):
                tx, ty = x + dx, y + dy
                if not (1 <= tx <= n and 1 <= ty <= m):
                    continue
                r = rng.random()
                if r < 0.15:
                    door[(x, y, tx, ty)] = door[(tx, ty, x, y)] = 0
                elif r < 0.40:
                    g = rng.randint(1, P)
                    door[(x, y, tx, ty)] = door[(tx, ty, x, y)] = g
    S = rng.randint(0, 6)
    keys = {}
    chosen = []
    for _ in range(S):
        x = rng.randint(1, n); y = rng.randint(1, m); q = rng.randint(1, P)
        chosen.append((x, y, q))
        keys[(x, y)] = keys.get((x, y), 0) | (1 << (q - 1))
    return n, m, P, door, keys, chosen

def render(n, m, P, door, chosen):
    lines = ['%d %d %d' % (n, m, P)]
    seen = set(); edges = []
    for (x, y, tx, ty), g in door.items():
        k = (min((x, y), (tx, ty)), max((x, y), (tx, ty)))
        if k in seen: continue
        seen.add(k)
        edges.append('%d %d %d %d %d' % (x, y, tx, ty, g))
    lines.append(str(len(edges)))
    lines += edges
    lines.append(str(len(chosen)))
    for (x, y, q) in chosen:
        lines.append('%d %d %d' % (x, y, q))
    return '\n'.join(lines) + '\n'

if __name__ == '__main__':
    exe = sys.argv[1]
    rng = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 1)
    N = int(sys.argv[3]) if len(sys.argv) > 3 else 2000
    bad = 0; dup_bad = 0; first = None
    for t in range(N):
        n, m, P, door, keys, chosen = gen(rng)
        inp = render(n, m, P, door, chosen)
        want = oracle(n, m, P, door, keys)
        r = subprocess.run([exe], input=inp.encode(), capture_output=True)
        got = r.stdout.decode().strip()
        if got != str(want):
            bad += 1
            cells = {}
            for (x, y, q) in chosen:
                cells[(x, y)] = cells.get((x, y), 0) + 1
            dup = any(v > 1 for v in cells.values())
            if dup: dup_bad += 1
            if first is None:
                first = (inp, got, want, dup)
    print('不一致 %d / %d   其中含「同格多钥匙」的 %d 个' % (bad, N, dup_bad))
    if first:
        print('首个反例 got=%s want=%s 同格多钥匙=%s' % (first[1], first[2], first[3]))
        print(first[0])
