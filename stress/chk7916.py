import random, subprocess, sys
from collections import deque

def ray_point(n, m, p):
    if p <= m:            return (1, p)
    if p <= m + n:        return (p - m, m)
    if p <= 2 * m + n:    return (n, 2 * m + n + 1 - p)
    return (2 * m + 2 * n + 1 - p, 1)

class Dinic:
    def __init__(self, n):
        self.n = n; self.g = [[] for _ in range(n)]
    def add(self, u, v, c):
        self.g[u].append([v, c, len(self.g[v])])
        self.g[v].append([u, 0, len(self.g[u]) - 1])
    def flow(self, s, t):
        res = 0
        while True:
            lev = [-1] * self.n; lev[s] = 0; q = deque([s])
            while q:
                u = q.popleft()
                for v, c, _ in self.g[u]:
                    if c > 0 and lev[v] < 0:
                        lev[v] = lev[u] + 1; q.append(v)
            if lev[t] < 0: return res
            it = [0] * self.n
            def dfs(u, f):
                if u == t: return f
                while it[u] < len(self.g[u]):
                    e = self.g[u][it[u]]
                    v, c, r = e
                    if c > 0 and lev[v] == lev[u] + 1:
                        d = dfs(v, min(f, c))
                        if d > 0:
                            e[1] -= d; self.g[v][r][1] += d
                            return d
                    it[u] += 1
                return 0
            while True:
                f = dfs(s, float('inf'))
                if f == 0: break
                res += f

def oracle(n, m, edges, pend):
    """pend = [((r,c), w, color), ((r,c), w, color)]，两色不同"""
    cells = [(r, c) for r in range(1, n + 1) for c in range(1, m + 1)]
    idx = {v: i for i, v in enumerate(cells)}
    S = len(cells); T = S + 1
    d = Dinic(T + 1)
    for (a, b), w in edges.items():
        if w: d.add(idx[a], idx[b], w); d.add(idx[b], idx[a], w)
    for (pt, w, col) in pend:
        if not w: continue
        if col == 0: d.add(S, idx[pt], w)
        else:        d.add(idx[pt], T, w)
    # 若同一点挂两个不同色端点，需特殊处理：见 gen 的断言
    return d.flow(S, T)

def gen(rng):
    while True:
        n = rng.randint(2, 4); m = rng.randint(2, 4)
        edges = {}
        for r in range(1, n + 1):
            for c in range(1, m + 1):
                if r < n: edges[((r, c), (r + 1, c))] = rng.randint(0, 9)
                if c < m: edges[((r, c), (r, c + 1))] = rng.randint(0, 9)
        total = 2 * (n + m)
        p1, p2 = rng.sample(range(1, total + 1), 2)
        a, b = ray_point(n, m, p1), ray_point(n, m, p2)
        t1, t2 = rng.randint(0, 1), rng.randint(0, 1)
        w1, w2 = rng.randint(0, 9), rng.randint(0, 9)
        if t1 == t2:
            want = 0
        elif a == b:
            # 同一个角点挂两个异色附加点：只能剪断其中一条悬挂边
            want = min(w1, w2)
        else:
            want = oracle(n, m, edges, [(a, w1, t1), (b, w2, t2)])
        return n, m, edges, (p1, w1, t1), (p2, w2, t2), want

def render(n, m, edges, q1, q2, T=1):
    L = ['%d %d %d' % (n, m, T)]
    for r in range(1, n):
        L.append(' '.join(str(edges[((r, c), (r + 1, c))]) for c in range(1, m + 1)))
    for r in range(1, n + 1):
        L.append(' '.join(str(edges[((r, c), (r, c + 1))]) for c in range(1, m)))
    L.append('2')
    for q in (q1, q2):
        L.append('%d %d %d' % (q[1], q[0], q[2]))
    return '\n'.join(L) + '\n'

if __name__ == '__main__':
    exe = sys.argv[1]
    rng = random.Random(int(sys.argv[2]) if len(sys.argv) > 2 else 1)
    N = int(sys.argv[3]) if len(sys.argv) > 3 else 400
    bad = 0
    for t in range(N):
        n, m, edges, q1, q2, want = gen(rng)
        inp = render(n, m, edges, q1, q2)
        r = subprocess.run([exe], input=inp.encode(), capture_output=True)
        got = r.stdout.decode().strip()
        if got != str(want):
            bad += 1
            if bad <= 3:
                print('MISMATCH got=%s want=%s' % (got, want)); print(inp)
    print('k=2 对拍 %d 组，不一致 %d' % (N, bad))
