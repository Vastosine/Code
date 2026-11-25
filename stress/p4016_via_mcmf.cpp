// 用 MCMF 模板重做 P4016 负载平衡，和他的 AC 版本对拍
#include <iostream>
#include "../OI/template/netflow/MCMF.cpp"

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vi a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];

    int s = 0, t = n + 1;
    MCMF_init(n + 2);
    for (int i = 1; i <= n; i++) addEdge(s, i, a[i], 0);
    for (int i = 1; i <= n; i++) addEdge(i, t, sum / n, 0);
    for (int i = 1; i <= n; i++) {
        int j = i % n + 1;
        addEdge(i, j, 1000000, 1);
        addEdge(j, i, 1000000, 1);
    }
    cout << MCMF(s, t).second << "\n";
    return 0;
}
