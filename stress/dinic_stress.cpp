// 随机对拍：OI/template/Dinic.cpp  vs  Edmonds-Karp 暴力
// 目的：11 个手写用例不覆盖「cur[u] 在增广成功后也 +1」这个细节，
//       这里用随机小图扫它的正确性（不是性能）。
#include <array>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include "../OI/template/netflow/Dinic.cpp"

using ll = long long;

struct EK {
    struct E { int to, nxt; ll cap; };
    std::vector<E> es;
    std::vector<int> head;
    EK(int n) : head(n, -1) {}
    void addEdge(int u, int v, ll c) {
        es.push_back({v, head[u], c}); head[u] = es.size() - 1;
        es.push_back({u, head[v], 0}); head[v] = es.size() - 1;
    }
    ll run(int s, int t) {
        ll ans = 0;
        int n = head.size();
        while (true) {
            std::vector<int> pe(n, -1), pv(n, -1);
            std::queue<int> q; q.push(s); pe[s] = -2;
            while (!q.empty() && pe[t] == -1) {
                int u = q.front(); q.pop();
                for (int i = head[u]; ~i; i = es[i].nxt)
                    if (es[i].cap > 0 && pe[es[i].to] == -1) {
                        pe[es[i].to] = i; pv[es[i].to] = u; q.push(es[i].to);
                    }
            }
            if (pe[t] == -1) return ans;
            ll f = (ll)4e18;
            for (int v = t; v != s; v = pv[v]) f = std::min(f, es[pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                es[pe[v]].cap -= f;
                es[pe[v] ^ 1].cap += f;
            }
            ans += f;
        }
    }
};

int main() {
    std::mt19937 rng(20261125);
    int fails = 0;
    for (int tc = 0; tc < 60000; tc++) {
        int n = 2 + rng() % 7;              // 2..8
        int m = rng() % (n * 3 + 1);        // 0..3n
        Dinic d(n);
        EK ek(n);
        std::vector<std::array<int, 3>> kept;
        for (int i = 0; i < m; i++) {
            int u = rng() % n, v = rng() % n;
            if (u == v) continue;
            int c = rng() % 6;              // 0..5，含 0 容量
            d.addEdge(u, v, c);
            ek.addEdge(u, v, c);
            kept.push_back({u, v, c});
        }
        int s = 0, t = n - 1;
        ll got = d.run(s, t), want = ek.run(s, t);
        if (got != want) {
            if (++fails <= 5) {
                printf("MISMATCH tc=%d n=%d s=%d t=%d got=%lld want=%lld\n", tc, n, s, t, got, want);
                for (auto &e : kept) printf("  %d -> %d cap %d\n", e[0], e[1], e[2]);
            }
        }
    }
    printf("%s  fails=%d / 60000\n", fails ? "**FAILED**" : "ALL PASS", fails);
    return fails != 0;
}
