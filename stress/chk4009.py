import heapq, random, itertools, sys

def solve(N, K, A, B, C, st, allow_back=True, build_mode='CA'):
    INF = float('inf')
    dist = [[[INF] * (K + 1) for _ in range(N + 1)] for _ in range(N + 1)]
    dist[1][1][K] = 0
    pq = [(0, 1, 1, K)]
    dirs = [(1, 0), (0, 1)] + ([(-1, 0), (0, -1)] if allow_back else [])
    while pq:
        d, x, y, f = heapq.heappop(pq)
        if d > dist[x][y][f]:
            continue
        if (x, y) == (N, N):
            return d
        if (x, y) not in st and f < K:
            nd = d + C + (A if build_mode == 'CA' else 0)
            if nd < dist[x][y][K]:
                dist[x][y][K] = nd
                heapq.heappush(pq, (nd, x, y, K))
        if f == 0:
            continue
        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if not (1 <= nx <= N and 1 <= ny <= N):
                continue
            w = B if (nx < x or ny < y) else 0
            nf = f - 1
            if (nx, ny) in st:
                nf = K
                w += A
            nd = d + w
            if nd < dist[nx][ny][nf]:
                dist[nx][ny][nf] = nd
                heapq.heappush(pq, (nd, nx, ny, nf))
    return dist[N][N]

# ---- 官方样例：9 3 2 3 6 ----
grid = """0 0 0 0 1 0 0 0 0
0 0 0 1 0 1 1 0 0
1 0 1 0 0 0 0 1 0
0 0 0 0 0 1 0 0 1
1 0 0 1 0 0 1 0 0
0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 1
1 0 0 1 0 0 0 1 0
0 1 0 0 0 0 0 0 0"""
N, K, A, B, C = 9, 3, 2, 3, 6
st = set()
for i, row in enumerate(grid.strip().split("\n")):
    for j, v in enumerate(row.split()):
        if v == '1':
            st.add((i + 1, j + 1))
print("样例答案应为 12")
print("  build = C+A   ->", solve(N, K, A, B, C, st, True, 'CA'))
print("  build = C     ->", solve(N, K, A, B, C, st, True, 'C'))
print("  只走右/下(C+A) ->", solve(N, K, A, B, C, st, False, 'CA'))
print()

# ---- 找反例：4 方向 vs 只走右/下 ----
random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 1)
found = 0
for trial in range(20000):
    n = random.randint(2, 4)
    k = random.randint(2, 3)
    a = random.randint(1, 8); b = random.randint(1, 8); c = random.randint(1, 8)
    cells = [(x, y) for x in range(1, n + 1) for y in range(1, n + 1)
             if (x, y) not in ((1, 1), (n, n))]
    p = random.choice([0.0, 0.2, 0.35, 0.5])
    s = set(q for q in cells if random.random() < p)
    full = solve(n, k, a, b, c, s, True, 'CA')
    mono = solve(n, k, a, b, c, s, False, 'CA')
    if full < mono:
        found += 1
        print("反例 #%d  N=%d K=%d A=%d B=%d C=%d" % (found, n, k, a, b, c))
        for x in range(1, n + 1):
            print("   " + " ".join(('1' if (x, y) in s else '0') for y in range(1, n + 1)))
        print("   4 方向最优 = %s   只走右/下 = %s" % (full, mono))
        if found >= 5:
            break
print("\n共找到", found, "个")
