// 用 MCMF 模板重做 P4014 分配问题，和他的 AC 版本对拍
#include <iostream>
#include "../OI/template/netflow/MCMF.cpp"

int main() {
    int n;
    if (!(cin >> n)) return 0;
    int s = 0, t = 2 * n + 1;
    MCMF_init(t + 1);
    for (int u = 1; u <= n; u++) {
        addEdge(s, u, 1, 0);
        addEdge(u + n, t, 1, 0);
        for (int v = 1; v <= n; v++) {
            int x;
            cin >> x;
            addEdge(u, v + n, 1, x);
        }
    }
    MCMF_snapshot();
    ll lo = MCMF(s, t, 1).second;
    MCMF_reset();
    ll hi = MCMF(s, t, -1).second;
    cout << lo << "\n" << hi << "\n";
    return 0;
}
