#include "netflow/BoundCostFlow.cpp"

int main() {
    szt n;
    cin >> n;
    BoundCostFlow a(n + 1);
    for (szt u = 1; u <= n; u++) {
        szt k;
        cin >> k;
        a.addEdge(u, 0, 0, INF, 0);
        while (k--) {
            szt v;
            ll w;
            cin >> v >> w;
            a.addEdge(u, v, 1, INF, w);
        }
    }
    cout << a.feasible(1, 0).second.second;
}