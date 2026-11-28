#include "Graph/Tarjan.cpp"
#include <vector>

int main() {
    szt n, m;
    cin >> n >> m;
    vst val(n + 1);
    for (szt i = 1; i <= n; i++) cin >> val[i];
    Tarjan g(n + 1);
    while (m--) {
        szt u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    auto &&[N, scc] = g.run();
    vector<vst> e(N);
    vst sum(N);
    for (szt i = 1; i <= n; i++) {
        sum[scc[i]] += val[i];
        for (szt v : g[i]) {
            if (scc[i] != scc[v]) e[scc[i]].push_back(scc[v]);
        }
    }
    vst in(N);
    for (szt i = 0; i < N; i++) {
        for (szt v : e[i]) {
            in[v]++;
        }
    }
    vst o, f(N);
    for (szt i = 0; i < N; i++) {
        if (!in[i]) o.push_back(i);
    }
    szt ans = 0;
    for (szt i = 0; i < o.size(); i++) {
        szt u = o[i];
        f[u] += sum[u];
        Max(ans, f[u]);
        for (szt v : e[u]) {
            Max(f[v], f[u]);
            if (!--in[v]) o.push_back(v);
        }
    }
    cout << ans;
}