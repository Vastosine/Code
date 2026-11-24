"""P7916 候选算法：对偶图 + 环形非交叉完美匹配 DP
用 Dinic 最小割作 oracle 验证。
"""
import heapq, random, sys, subprocess
from collections import deque

# ---------- 射线编号 -> 格点（1-indexed） ----------
def ray_point(n, m, p):
    if p <= m:            return (1, p)
    if p <= m + n:        return (p - m, m)
    if p <= 2 * m + n:    return (n, 2 * m + n + 1 - p)
    return (2 * m + 2 * n + 1 - p, 1)

def ray_before(n, m, i):
    """射线 i 之后那条边界边（若无则 None）：返回 (格点1, 格点2)"""
    a = ray_point(n, m, i)
    b = ray_point(n, m, i % (2 * (n + m)) + 1)
    return None if a == b else (a, b)

def boundary_edge_of(pos, n, m, w):
    """边界边 -> (相邻内面, 权重)"""
    (r1, c1), (r2, c2) = pos
    if r1 == r2:                      # 水平
        c = min(c1, c2)
        if r1 == 1:   return (1, c)
        if r1 == n:   return (n - 1, c)
    else:                             # 竖直
        r = min(r1, r2)
        if c1 == 1:   return (r, 1)
        if c1 == m:   return (r, m - 1)
    raise AssertionError((r1, c1, r2, c2, n, m))

def candidate(n, m, edges, terms):
    """terms: [(p, w, color)]  返回候选答案"""
    k = len(terms)
    if k <= 1:
        return 0
    terms = sorted(terms, key=lambda t: t[0])
    F = (n - 1) * (m - 1)
    fid = lambda r, c: (r - 1) * (m - 1) + (c - 1)
    N = F + k
    arc = lambda j: F + j                      # 弧 j = 从 t_j 到 t_{j+1}
    g = [[] for _ in range(N)]
    def add(u, v, w):
        g[u].append((v, w)); g[v].append((u, w))

    # 内部边 -> 两个内面
    for r in range(1, n + 1):
        for c in range(1, m + 1):
            if r < n and 1 < c < m:
                add(fid(r, c - 1), fid(r, c), edges[((r, c), (r + 1, c))])
            if c < m and 1 < r < n:
                add(fid(r - 1, c), fid(r, c), edges[((r, c), (r, c + 1))])
    # 边界边 -> 内面 + 弧
    P = 2 * (n + m)
    ps = [t[0] for t in terms]
    for i in range(1, P + 1):
        pos = ray_before(n, m, i)
        if pos is None:
            continue
        fr = boundary_edge_of(pos, n, m, None)
        # 这条边属于哪条弧：找最大的 j 使 ps[j] <= i（环形）
        # 用「i 落在 (p_j, p_{j+1}] 的哪个区间」判断
        j = None
        for jj in range(k):
            lo = ps[jj]; hi = ps[(jj + 1) % k]
            inside = (lo <= i < hi) if lo < hi else (i >= lo or i < hi)
            if inside:
                j = jj; break
        assert j is not None, (i, ps)
        add(arc(j), fid(*fr), edges[(pos[0], pos[1])] if (pos[0], pos[1]) in edges
            else edges[(pos[1], pos[0])])
    # 悬挂边 -> 相邻两条弧
    for j, (p, w, c) in enumerate(terms):
        add(arc((j - 1) % k), arc(j), w)

    # 弧间最短路
    def dij(s):
        d = [1 << 60] * N; d[s] = 0; pq = [(0, s)]; done = [False] * N
        while pq:
            du, u = heapq.heappop(pq)
            if done[u]: continue
            done[u] = True
            for v, w in g[u]:
                if du + w < d[v]:
                    d[v] = du + w; heapq.heappush(pq, (du + w, v))
        return d
    D = [dij(arc(j)) for j in range(k)]

    # 异色交界
    cols = [t[2] for t in terms]
    S = [j for j in range(k) if cols[j] != cols[(j + 1) % k]]
    if not S:
        return 0
    if len(S) % 2:
        return None                      # 不该发生
    t = len(S)
    f = [[0] * t for _ in range(t)]
    for length in range(2, t + 1, 2):
        for l in range(0, t - length + 1):
            r = l + length - 1
            best = 1 << 60
            for j in range(l + 1, r + 1, 2):
                v = D[S[l]][arc(S[j])] + (f[l + 1][j - 1] if j - 1 >= l + 1 else 0) \
                    + (f[j + 1][r] if j + 1 <= r else 0)
                best = min(best, v)
            f[l][r] = best
    return f[0][t - 1]

# ---------- oracle ----------
class Dinic:
    def __init__(self, n): self.n = n; self.g = [[] for _ in range(n)]
    def add(self, u, v, c):
        self.g[u].append([v, c, len(self.g[v])]); self.g[v].append([u, 0, len(self.g[u]) - 1])
    def flow(self, s, t):
        res = 0
        while True:
            lev = [-1] * self.n; lev[s] = 0; q = deque([s])
            while q:
                u = q.popleft()
                for v, c, _ in self.g[u]:
                    if c > 0 and lev[v] < 0: lev[v] = lev[u] + 1; q.append(v)
            if lev[t] < 0: return res
            it = [0] * self.n
            def dfs(u, f):
                if u == t: return f
                while it[u] < len(self.g[u]):
                    e = self.g[u][it[u]]; v, c, r = e
                    if c > 0 and lev[v] == lev[u] + 1:
                        d = dfs(v, min(f, c))
                        if d > 0: e[1] -= d; self.g[v][r][1] += d; return d
                    it[u] += 1
                return 0
            while True:
                f = dfs(s, 1 << 60)
                if f == 0: break
                res += f

def oracle(n, m, edges, terms):
    cells = [(r, c) for r in range(1, n + 1) for c in range(1, m + 1)]
    idx = {v: i for i, v in enumerate(cells)}
    S = len(cells); T = S + 1
    d = Dinic(T + 1)
    for (a, b), w in edges.items():
        if w: d.add(idx[a], idx[b], w); d.add(idx[b], idx[a], w)
    for (p, w, c) in terms:
        if not w: continue
        pt = idx[ray_point(n, m, p)]
        if c == 0: d.add(S, pt, w)
        else:      d.add(pt, T, w)
    return d.flow(S, T)

if __name__ == '__main__':
    rng = random.Random(int(sys.argv[1]) if len(sys.argv) > 1 else 1)
    TRIALS = int(sys.argv[2]) if len(sys.argv) > 2 else 500
    bad = 0
    for t in range(TRIALS):
        n = rng.randint(2, 4); m = rng.randint(2, 4)
        edges = {}
        for r in range(1, n + 1):
            for c in range(1, m + 1):
                if r < n: edges[((r, c), (r + 1, c))] = rng.randint(0, 9)
                if c < m: edges[((r, c), (r, c + 1))] = rng.randint(0, 9)
        k = rng.randint(1, min(6, 2 * (n + m)))
        ps = rng.sample(range(1, 2 * (n + m) + 1), k)
        terms = [(p, rng.randint(0, 9), rng.randint(0, 1)) for p in ps]
        want = oracle(n, m, edges, terms)
        got = candidate(n, m, edges, terms)
        if got != want:
            bad += 1
            if bad <= 5:
                print('DIFF n=%d m=%d got=%s want=%s' % (n, m, got, want))
                print('  terms', terms)
    print('%d 组，不一致 %d' % (TRIALS, bad))
