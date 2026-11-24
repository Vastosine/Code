// P7916 参考实现（不是他的文件，只放在 stress/ 供对照）
// 对偶图 + 环形非交叉完美匹配区间 DP
// 已用 Dinic 最小割 oracle 对拍：样例 12；随机 2300 组 0 不一致
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1ll << 60;

int n, m, T, P, F;

void ray_point(int p, int &r, int &c) {          // p: 1..2(n+m)
    if (p <= m)            r = 1, c = p;
    else if (p <= m + n)   r = p - m, c = m;
    else if (p <= 2 * m + n) r = n, c = 2 * m + n + 1 - p;
    else                   r = 2 * m + 2 * n + 1 - p, c = 1;
}

int main() {
    scanf("%d %d %d", &n, &m, &T);
    vector<vector<ll>> x1(n + 1, vector<ll>(m + 1));   // (r,c)-(r+1,c)  1<=r<n
    vector<vector<ll>> x2(n + 1, vector<ll>(m + 1));   // (r,c)-(r,c+1)  1<=c<m
    for (int r = 1; r < n; r++)
        for (int c = 1; c <= m; c++) scanf("%lld", &x1[r][c]);
    for (int r = 1; r <= n; r++)
        for (int c = 1; c < m; c++) scanf("%lld", &x2[r][c]);

    F = (n - 1) * (m - 1);
    P = 2 * (n + m);
    auto face = [&](int r, int c) { return (r - 1) * (m - 1) + (c - 1); };

    // 静态部分：内面之间的边（与询问无关）
    vector<vector<pair<int, ll>>> base(F ? F : 1);
    for (int r = 1; r < n; r++)
        for (int c = 1; c <= m; c++)
            if (1 < c && c < m) {
                int u = face(r, c - 1), v = face(r, c);
                base[u].push_back({v, x1[r][c]});
                base[v].push_back({u, x1[r][c]});
            }
    for (int r = 1; r <= n; r++)
        for (int c = 1; c < m; c++)
            if (1 < r && r < n) {
                int u = face(r - 1, c), v = face(r, c);
                base[u].push_back({v, x2[r][c]});
                base[v].push_back({u, x2[r][c]});
            }

    while (T--) {
        int k; scanf("%d", &k);
        vector<int> pp(k); vector<ll> ww(k); vector<int> cc(k);
        for (int i = 0; i < k; i++) scanf("%lld %d %d", &ww[i], &pp[i], &cc[i]);
        // 按射线编号排序 = 圆周顺序
        vector<int> id(k);
        for (int i = 0; i < k; i++) id[i] = i;
        sort(id.begin(), id.end(), [&](int a, int b) { return pp[a] < pp[b]; });
        vector<int> p(k); vector<ll> w(k); vector<int> col(k);
        for (int i = 0; i < k; i++) p[i] = pp[id[i]], w[i] = ww[id[i]], col[i] = cc[id[i]];

        if (k <= 1) { puts("0"); continue; }

        int N = F + k;
        vector<vector<pair<int, ll>>> g(N);
        for (int u = 0; u < F; u++) { g[u] = base[u]; }

        // 边界边 -> 相邻内面 + 它所在的弧
        for (int i = 1; i <= P; i++) {
            int r1, c1, r2, c2;
            ray_point(i, r1, c1);
            ray_point(i % P + 1, r2, c2);
            if (r1 == r2 && c1 == c2) continue;      // 角上两条射线同一格点，中间没有边
            int fr, fc; ll wgt;
            if (r1 == r2) {                          // 水平边界边
                int c = min(c1, c2);
                fr = (r1 == 1 ? 1 : n - 1); fc = c; wgt = x2[r1][c];
            } else {                                 // 竖直边界边
                int r = min(r1, r2);
                fr = r; fc = (c1 == 1 ? 1 : m - 1); wgt = x1[r][c1];
            }
            // 这条边属于弧 j  <=>  p[j] <= i < p[j+1]  （环形）
            int j = -1;
            for (int jj = 0; jj < k; jj++) {
                int lo = p[jj], hi = p[(jj + 1) % k];
                bool in = (lo < hi) ? (lo <= i && i < hi) : (i >= lo || i < hi);
                if (in) { j = jj; break; }
            }
            int a = face(fr, fc), b = F + j;
            g[a].push_back({b, wgt});
            g[b].push_back({a, wgt});
        }
        // 悬挂边 j：弧(j-1) — 弧 j
        for (int j = 0; j < k; j++) {
            int a = F + (j - 1 + k) % k, b = F + j;
            g[a].push_back({b, w[j]});
            g[b].push_back({a, w[j]});
        }

        // 异色交界
        vector<int> S;
        for (int j = 0; j < k; j++)
            if (col[j] != col[(j + 1) % k]) S.push_back(j);
        if (S.empty()) { puts("0"); continue; }
        int t = (int) S.size();

        // 每个 S 成员各跑一次 Dijkstra
        vector<vector<ll>> D(t, vector<ll>(t, INF));
        for (int a = 0; a < t; a++) {
            vector<ll> d(N, INF);
            vector<char> done(N, 0);
            priority_queue<pair<ll, int>> pq;
            int src = F + S[a];
            d[src] = 0; pq.push({0, src});   // max-heap 存负距离
            while (!pq.empty()) {
                auto [ndu, u] = pq.top(); pq.pop(); ll du = -ndu;
                if (done[u]) continue;
                done[u] = 1;
                for (auto [v, wv] : g[u])
                    if (du + wv < d[v]) { d[v] = du + wv; pq.push({-(du + wv), v}); }
            }
            for (int b = 0; b < t; b++) D[a][b] = d[F + S[b]];
        }

        // 圆周上非交叉完美匹配
        vector<vector<ll>> dp(t, vector<ll>(t, 0));
        for (int len = 2; len <= t; len += 2)
            for (int l = 0; l + len - 1 < t; l++) {
                int r = l + len - 1;
                ll best = INF;
                for (int j = l + 1; j <= r; j += 2) {
                    ll v = D[l][j];
                    if (j - 1 >= l + 1) v += dp[l + 1][j - 1];
                    if (j + 1 <= r) v += dp[j + 1][r];
                    best = min(best, v);
                }
                dp[l][r] = best;
            }
        printf("%lld\n", dp[0][t - 1]);
    }
    return 0;
}
