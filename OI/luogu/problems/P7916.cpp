// Problem : P7916 [CSP-S 2021] 交通规划 https://www.luogu.com.cn/problem/P7916
// Time    : 2026-11-24 13:11:36
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

vll Dijkstra(int s, const vector<vector<pll>> &e, int n) {
    vi vis(n + 1, 0);
    vll dis(n + 1, 1ll << 60);
    dis[s] = 0;
    priority_queue<pll> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
            auto nd = w + dis[u];
            if (nd < dis[v]) {
                dis[v] = nd;
                q.push({-nd, v});
            }
        }
    }
    return dis;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, T;
    cin >> n >> m >> T;
    auto f = [&] (int x, int y) {
        return x * (m + 1) + y;
    };
    int N = (n + 1) * (m + 1);
    auto addEdge = [&] (int u, int v, ll w, auto &e) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    };
    // [0, 2n + 2m)
    auto g = [&] (int x) {
        if (x < m) return f(0, x);
        if (x < m + n) return f(x - m, m);
        if (x < m * 2 + n) return f(n, m - (x - m - n));
        return f(n - (x - m * 2 - n), 0);
    };
    vector<vector<pll>> E(N);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll w;
            cin >> w;
            int u = f(i, j), v = f(i, j + 1);
            addEdge(u, v, w, E);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            ll w;
            cin >> w;
            int u = f(i, j), v = f(i + 1, j);
            addEdge(u, v, w, E);
        }
    }
    while (T--) {
        auto e = E;
        int k;
        cin >> k;
        vector<vll> a(k, vll(3));
        int M = 2 * m + 2 * n;
        vll use(M), col(M, -1);
        cin >> a;
        // if (k > 2) continue;
        // if (k < 2 || a[0][2] == a[1][2]) {
        //     cout << "0\n";
        //     continue;
        // }
        for (int i = 0; i < k; i++) {
            use[a[i][1] - 1] = a[i][0];
            col[a[i][1] - 1] = a[i][2];
        }
        vi p;
        for (int i = 0; i < M; i++) {
            addEdge(g(i), g((i + 1) % M), use[i], e);
            if (~col[i] && (p.empty() || (col[p.back()] != col[i]))) p.push_back(i);
        }
        while (!p.empty() && col[p[0]] == col[p.back()]) {
            p = vi(p.begin() + 1, p.end());
        }
        int pn = (int) p.size();
        if (!pn) {
            cout << "0\n";
            continue;
        }
        e.resize(N);
        vector<vll> G(pn, vll(pn)), dp(pn + 1, vll(pn + 1, INF));
        for (int i = 0; i < pn; i += 2) {
            vll res = Dijkstra(g(p[i]), e, e.size());
            for (int j = 1; j < pn; j++) {
                G[i][j] = G[j][i] = res[g(p[j])];
            }
        }
        for (int i = 1; i < pn; i++) {
            dp[i - 1][i] = G[i - 1][i];
            for (int j = 0; j < i; j++) dp[i][j] = 0;
        }
        for (int i = 1; i <= pn; i++) {
            for (int j = 0; j < i; j++) dp[i][j] = 0;
        }
        for (int d = 4; d <= pn; d += 2) {
            for (int l = 0; l + d <= pn; l++) {
                int r = l + d - 1;
                for (int t = l + 1; t <= r; t += 2) {
                    dp[l][r] = min(dp[l][r], G[l][t] + dp[l + 1][t - 1] + dp[t + 1][r]);
                }
            }
        }
        cout << dp[0][pn - 1] << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
