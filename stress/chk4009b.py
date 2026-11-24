import heapq, random, sys

def solve(N, K, A, B, C, st, allow_back=True, build_when='any'):
    INF = float('inf')
    dist = [[[INF] * (K + 1) for _ in range(N)] for _ in range(N)]
    dist[0][0][K] = 0
    pq = [(0, 0, 0, K)]
    dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    if not allow_back:
        dirs = [(1, 0), (0, 1)]
    while pq:
        d, x, y, f = heapq.heappop(pq)
        if d > dist[x][y][f]:
            continue
        # 他在油库上：强制加满
        if f != K and (x, y) in st:
            nd = d + A
            if nd < dist[x][y][K]:
                dist[x][y][K] = nd
                heapq.heappush(pq, (nd, x, y, K))
            continue
        # 建站：'any' = f<K 都行；'zero' = 只有 f==0 行（他现在代码里的写法）
        if (x, y) not in st and (f < K if build_when == 'any' else f == 0):
            nd = d + C + A
            if nd < dist[x][y][K]:
                dist[x][y][K] = nd
                heapq.heappush(pq, (nd, x, y, K))
        if f == 0:
            continue
        for dx, dy in dirs:
            vx, vy = x + dx, y + dy
            if not (0 <= vx < N and 0 <= vy < N):
                continue
            nd = d + (B if vx + vy < x + y else 0)
            if nd < dist[vx][vy][f - 1]:
                dist[vx][vy][f - 1] = nd
                heapq.heappush(pq, (nd, vx, vy, f - 1))
    return min(dist[N - 1][N - 1])

if __name__ == '__main__':
    random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 1)
    bad = 0
    for trial in range(int(sys.argv[2]) if len(sys.argv) > 2 else 60000):
        n = random.randint(2, 5); k = random.randint(2, 4)
        a = random.randint(1, 6); b = random.randint(1, 6); c = random.randint(1, 10)
        cells = [(x, y) for x in range(n) for y in range(n) if (x, y) not in ((0, 0), (n - 1, n - 1))]
        p = random.choice([0.1, 0.25, 0.4])
        s = set(q for q in cells if random.random() < p)
        anyf = solve(n, k, a, b, c, s, True, 'any')
        zero = solve(n, k, a, b, c, s, True, 'zero')
        if zero > anyf:
            bad += 1
            print('DIFF n=%d k=%d A=%d B=%d C=%d  any=%s zero=%s' % (n, k, a, b, c, anyf, zero))
            for x in range(n):
                print('   ' + ' '.join('1' if (x, y) in s else '0' for y in range(n)))
            if bad >= 3:
                break
    print('mismatch(只在 f==0 才建站 更差) =', bad)
