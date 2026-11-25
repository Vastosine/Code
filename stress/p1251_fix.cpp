// P1251 标准建模：r_i 挂在 s->脏 和 净->t 上，最大流被钉成 Σr_i
#include <iostream>
#include "../OI/template/netflow/MCMF.cpp"

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vll r(n);
    for (int i = 0; i < n; i++) cin >> r[i];
    ll p, f, s;
    int m, slow;
    cin >> p >> m >> f >> slow >> s;

    int S = 0, T = 2 * n + 1;
    const ll BIG = 40000000000LL;
    MCMF_init(T + 1);
    for (int i = 1; i <= n; i++) {
        addEdge(S, i + n, r[i - 1], 0);   // 第 i 天产生 r_i 块脏餐巾
        addEdge(i, T, r[i - 1], 0);       // 第 i 天需要 r_i 块干净的
        addEdge(S, i, BIG, p);            // 买
        if (i < n) addEdge(i + n, i + n + 1, BIG, 0);          // 脏的留存
        if (i + m <= n) addEdge(i + n, i + m, BIG, f);         // 快洗
        if (i + slow <= n) addEdge(i + n, i + slow, BIG, s);   // 慢洗
    }
    pll res = MCMF(S, T);
    cout << res.second << "\n";
    ll tot = 0;
    for (int i = 0; i < n; i++) tot += r[i];
    cerr << "flow=" << res.first << " sum r=" << tot << (res.first == tot ? "" : "  **NOT PINNED**") << "\n";
    return 0;
}
