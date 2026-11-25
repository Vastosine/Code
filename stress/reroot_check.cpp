// reroot_check.cpp -- OI/template/reroot.cpp 的对拍
//   ① build() 的 fa / dep / o / s      vs 暴力 BFS
//   ② 档① 标量（P3478 点数版）          vs 每个根各跑一次 BFS 求深度和
//   ③ 档② 整表 + 哨兵（P3047 距离类）    vs 每个根各跑一次 BFS 求 K 邻域和
//   ④ Top2                              vs 排序暴力
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <queue>
#include <random>
#include "reroot_ref_1121.cpp"

std::mt19937_64 rng(20261121ULL);

void genTree(Reroot &R, int n) {
    R.init(n);
    vi lab(n + 1);
    std::iota(lab.begin() + 1, lab.end(), 1);
    std::shuffle(lab.begin() + 1, lab.end(), rng);
    for (int v = 2; v <= n; v++) {
        int p = (int) (rng() % (v - 1)) + 1;
        R.addEdge(lab[v], lab[p]);
    }
}

// 暴力 BFS：从 s 出发的距离
vi bfsDist(const vector<vi> &e, int n, int s) {
    vi d(n + 1, -1);
    std::queue<int> q;
    d[s] = 0, q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : e[u])
            if (d[v] < 0) d[v] = d[u] + 1, q.push(v);
    }
    return d;
}

int main() {
    int badBuild = 0, badCsr = 0, badTier1 = 0, badTier2 = 0, badTop2 = 0;
    int T = 3000;
    for (int tc = 0; tc < T; tc++) {
        int n = 2 + (int) (rng() % 7);
        int K = 1 + (int) (rng() % 4);
        vi a(n + 1);
        for (int i = 1; i <= n; i++) a[i] = (int) (rng() % 20);

        Reroot R;
        genTree(R, n);
        R.build(1);

        // ---------- ① build ----------
        vi bd = bfsDist(R.e, n, 1);
        vi bfa(n + 1, 0);
        std::queue<int> q;
        q.push(1), bfa[1] = 0;
        vi seen(n + 1, 0);
        seen[1] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : R.e[u])
                if (!seen[v]) seen[v] = 1, bfa[v] = u, q.push(v);
        }
        bool ok = ((int) R.o.size() == n);
        for (int u = 1; u <= n && ok; u++) {
            if (R.dep[u] != bd[u] + 1) ok = false;
            if (R.fa[u] != (u == 1 ? 0 : bfa[u])) ok = false;
            vi kids;
            for (int v : R.e[u])
                if (R.fa[v] == u) kids.push_back(v);
            if ((int) kids.size() != (int) R.s[u].size()) ok = false;
            for (int v : kids) {
                bool found = false;
                for (int w : R.s[u]) found |= (w == v);
                if (!found) ok = false;
            }
        }
        // 父亲必须排在儿子前面
        vi pos(n + 1, 0);
        for (int i = 0; i < (int) R.o.size(); i++) pos[R.o[i]] = i;
        for (int u = 2; u <= n && ok; u++)
            if (pos[R.fa[u]] > pos[u]) ok = false;
        if (!ok) badBuild++;

        // ---------- ①b CSR 儿子表 vs s ----------
        Reroot R2;
        R2.init(n);
        for (int u = 1; u <= n; u++)
            for (int v : R.e[u]) R2.addEdge(u, v);
        R2.build(1);
        R2.buildChildrenCSR();
        bool okc = true;
        for (int u = 1; u <= n; u++) {
            vi got;
            for (int i = R2.cstart[u]; i < R2.cstart[u + 1]; i++) got.push_back(R2.cadj[i]);
            std::sort(got.begin(), got.end());
            vi want = R.s[u];
            std::sort(want.begin(), want.end());
            if (got != want) okc = false;
        }
        if (!okc) badCsr++;

        // ---------- ② 档①：P3478 点数版 ----------
        vi siz(n + 1, 0);
        R.down([&](int u) {
            siz[u] = 1;
            for (int v : R.s[u]) siz[u] += siz[v];
        });
        ll base = 0;
        for (int u = 1; u <= n; u++) base += bd[u];
        std::vector<ll> res(n + 1, 0);
        res[1] = base;
        R.up([&](int u) {
            if (u == 1) return;
            res[u] = res[R.fa[u]] + (ll) n - 2LL * siz[u];
        });
        bool ok1 = true;
        for (int u = 1; u <= n; u++) {
            vi d = bfsDist(R.e, n, u);
            ll want = 0;
            for (int v = 1; v <= n; v++) want += d[v];
            if (res[u] != want) ok1 = false;
        }
        if (!ok1) badTier1++;

        // ---------- ③ 档②：P3047 距离类（哨兵列，下标 = 距离 + 2）----------
        vector<vi> f(n + 1, vi(K + 3, 0)), g(n + 1, vi(K + 3, 0));
        R.down([&](int u) {
            f[u][2] = a[u];
            for (int v : R.s[u])
                for (int d = 0; d + 1 <= K; d++) f[u][d + 3] += f[v][d + 2];
        });
        R.up([&](int u) {
            if (u == 1) {
                g[u] = f[u];
                return;
            }
            int p = R.fa[u];
            g[u][2] = a[u];
            for (int k = 1; k <= K; k++)
                g[u][k + 2] = f[u][k + 2] + g[p][k - 1 + 2] - f[u][k - 2 + 2];
        });
        bool ok2 = true;
        for (int u = 1; u <= n; u++) {
            vi d = bfsDist(R.e, n, u);
            ll want = 0;
            for (int v = 1; v <= n; v++)
                if (d[v] <= K) want += a[v];
            ll got = 0;
            for (int k = 0; k <= K; k++) got += g[u][k + 2];
            if (got != want) ok2 = false;
        }
        if (!ok2) badTier2++;

        // ---------- ④ Top2 ----------
        Top2 t;
        t.clear();
        vi vals;
        int m = 1 + (int) (rng() % 6);
        for (int i = 0; i < m; i++) {
            int x = (int) (rng() % 5);   // 小值域，故意制造重复的最大值
            vals.push_back(x);
            t.add(x);
        }
        std::sort(vals.begin(), vals.end());
        if (t.best() != vals.back()) badTop2++;
        for (int x : vals) {
            vi rest;
            bool removed = false;
            for (int y : vals) {
                if (!removed && y == x) { removed = true; continue; }
                rest.push_back(y);
            }
            ll want = rest.empty() ? -(1ll << 60) : rest.back();
            if (t.best(x) != want) badTop2++;
        }
    }
    std::printf("T = %d\n", T);
    std::printf("build   bad = %d\n", badBuild);
    std::printf("csr     bad = %d\n", badCsr);
    std::printf("tier1   bad = %d\n", badTier1);
    std::printf("tier2   bad = %d\n", badTier2);
    std::printf("top2    bad = %d\n", badTop2);
    return (badBuild + badCsr + badTier1 + badTier2 + badTop2) ? 1 : 0;
}
