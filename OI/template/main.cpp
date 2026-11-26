#include "netflow/BoundCostFlow.cpp"

int main() {
    szt n, m, s, t;
    cin >> n >> m >> s >> t;
    NegMCMF g(n + 1);
    while (m--) {
        szt u, v;
        ll c, w;
        cin >> u >> v >> c >> w;
        g.addEdge(u, v, c, w);
    }
    auto res = g.run(s, t);
    cout << res.first << " " << res.second;
}