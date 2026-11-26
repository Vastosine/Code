#include "netflow/BoundCostFlow.cpp"
#include <algorithm>

int main() {
    szt n, m;
    cin >> n >> m;
    vll a(n);
    cin >> a;
    ll mx = *max_element(a.begin(), a.end());
    szt s = 0, t = n + 1, N = t + 1;
    BoundCostFlow g(N);
    g.addEdge(s, 1, mx, mx, 0);
    for (szt i = 1; i <= n; i++) {
        g.addEdge(i, i + 1, 0, mx - a[i - 1], 0);
        g.addEdge(i + 1, i, 0, INF, 0);
    }
    while (m--) {
        szt u, v;
        ll w;
        cin >> u >> v >> w;
        g.addEdge(u, v + 1, 0, INF, w);
    }
    cout << g.feasible(s, t).second.second;
}