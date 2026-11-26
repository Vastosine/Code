#include "netflow/BoundCostFlow.cpp"

int main() {
    szt n;
    ll m;
    cin >> n >> m;
    szt s = n * 2 + 1, t = s + 1, N = t + 1, S = 0;
    BoundCostFlow a(N);
    a.addEdge(s, S, m, m, 0);
    a.addEdge(S, t, 0, INF, 0);
    for (szt i = 1; i <= n; i++) {
        a.addEdge(S, i, 0, m, 0);
        a.addEdge(i + n, t, 0, m, 0);
        ll v;
        cin >> v;
        a.addEdge(i, i + n, v, v, 0);
    }
    for (szt i = 1; i < n; i++) {
        for (szt j = i + 1; j <= n; j++) {
            ll c;
            cin >> c;
            if (c >= 0) a.addEdge(i + n, j, 0, m, c);
        }
    }
    cout << a.feasible(s, t).second.second;
}