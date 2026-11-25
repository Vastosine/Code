// reroot_big.cpp -- 边界与规模：n = 1、n = 1e6 的链、n = 1e6 的菊花
#include <cstdio>
#include <ctime>
#include "reroot_ref_1121.cpp"

static double now() { return (double) clock() / CLOCKS_PER_SEC; }

int main() {
    // n = 1
    {
        Reroot R;
        R.init(1);
        R.build(1);
        vi siz(2, 0);
        R.down([&](int u) { siz[u] = 1; });
        R.up([&](int u) { (void) u; });
        std::printf("n=1     o=%d  fa[1]=%d  dep[1]=%d  siz[1]=%d\n",
                    (int) R.o.size(), R.fa[1], R.dep[1], siz[1]);
    }

    const int N = 1000000;
    // 链
    {
        double t0 = now();
        Reroot R;
        R.init(N);
        for (int i = 1; i < N; i++) R.addEdge(i, i + 1);
        R.build(1);
        std::vector<ll> siz(N + 1, 0), res(N + 1, 0);
        R.down([&](int u) {
            siz[u] = 1;
            for (int v : R.s[u]) siz[u] += siz[v];
        });
        ll base = 0;
        for (int u = 1; u <= N; u++) base += R.dep[u] - 1;
        res[1] = base;
        R.up([&](int u) {
            if (u == 1) return;
            res[u] = res[R.fa[u]] + (ll) N - 2LL * siz[u];
        });
        ll mx = 0;
        for (int u = 1; u <= N; u++) if (res[u] > mx) mx = res[u];
        std::printf("chain   o=%d  dep[N]=%d  siz[1]=%lld  max=%.0f  %.2fs\n",
                    (int) R.o.size(), R.dep[N], siz[1], (double) mx, now() - t0);
        // 链上根取端点时深度和 = N(N-1)/2；中点最小，端点最大
        std::printf("        expect N(N-1)/2 = %lld  -> %s\n",
                    (ll) N * (N - 1) / 2, mx == (ll) N * (N - 1) / 2 ? "OK" : "MISMATCH");
    }
    // 菊花
    {
        double t0 = now();
        Reroot R;
        R.init(N);
        for (int i = 2; i <= N; i++) R.addEdge(1, i);
        R.build(1);
        vi siz(N + 1, 0);
        R.down([&](int u) {
            siz[u] = 1;
            for (int v : R.s[u]) siz[u] += siz[v];
        });
        std::printf("star    o=%d  siz[1]=%d  s[1]=%d  %.2fs\n",
                    (int) R.o.size(), siz[1], (int) R.s[1].size(), now() - t0);
    }
    return 0;
}
