// P1251 用他的模型实现：后_i -> t(INF) / s -> 前_i(INF, p) / 前_i -> 后_i(r_i) /
// 前_i -> 前_{i+1} / 后_i -> 前_{i+m}(f) / 后_i -> 前_{i+n}(s)
#include <iostream>
#include "../OI/template/netflow/MCMF.cpp"

int main() {
    int N;
    if (!(cin >> N)) return 0;
    vll r(N + 1);
    for (int i = 1; i <= N; i++) cin >> r[i];
    ll p, f, s;
    int m, n;
    cin >> p >> m >> f >> n >> s;

    int S = 0, T = 2 * N + 1;
    const ll BIG = 40000000000LL;      // > Σr，当成 INF
    MCMF_init(T + 1);
    ll tot = 0;
    for (int i = 1; i <= N; i++) tot += r[i];
    for (int i = 1; i <= N; i++) {
        addEdge(S, i, BIG, p);                 // 买
        addEdge(i, i + N, r[i], 0);            // 当天用掉
        addEdge(i + N, T, BIG, 0);             // 丢掉脏的
        if (i < N) addEdge(i, i + 1, BIG, 0);  // 干净的留到明天
        if (i + m <= N) addEdge(i + N, i + m, BIG, f);   // 快洗
        if (i + n <= N) addEdge(i + N, i + n, BIG, s);   // 慢洗
    }
    pll res = MCMF(S, T);
    cout << res.second << "\n";
    cerr << "flow=" << res.first << " tot=" << tot << (res.first == tot ? "" : "  **FLOW != SUM r**") << "\n";
    return 0;
}
