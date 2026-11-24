// Problem : P4011 孤岛营救问题 https://www.luogu.com.cn/problem/P4011
// Time    : 2026-11-24 11:06:25
#include <algorithm>
#include <iostream>
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

auto Main([[maybe_unused]] int C = 0) {
    int n, m, P, K, S;
    cin >> n >> m >> P >> K;
    auto f = [&] (int x, int y) { return (x - 1) * m + y - 1; };
    int N = n * m;
    vector<vi> a(N, vi(N, -1));
    vi b(N);
    while (K--) {
        int x1, y1, x2, y2, g;
        cin >> x1 >> y1 >> x2 >> y2 >> g;
        int u = f(x1, y1), v = f(x2, y2);
        a[u][v] = a[v][u] = g;
    }
    cin >> S;
    while (S--) {
        int x, y, g;
        cin >> x >> y >> g;
        b[f(x, y)] |= (1 << (g - 1));
    }
    vector<pair<pii, int>> o(1, {{1, 1}, 0});
    vector<vi> vis(N, vi(1 << P)), dis(N, vi(1 << P, inf));
    const int dir[][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    vis[0][0] = 1;
    dis[0][0] = 0;
    for (int i = 0; i < (int) o.size(); i++) {
        auto [p, mask] = o[i];
        auto &[x, y] = p;
        int u = f(x, y);
        int t = mask | b[u];
        for (auto &[dx, dy] : dir) {
            int tx = x + dx, ty = y + dy;
            if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
            int v = f(tx, ty);
            if (!a[u][v] || (a[u][v] > 0 && !((1 << (a[u][v] - 1)) & t)) || vis[v][t]) continue;
            int nd = dis[u][mask] + 1;
            if (nd < dis[v][t]) {
                dis[v][t] = nd;
                o.push_back({{tx, ty}, t});
                vis[v][t] = 1;
            }
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         int u = f(i, j);
    //         int ans = *min_element(dis[u].begin(), dis[u].end());
    //         cout << (ans == inf ? -1 : ans) << " ";
    //     }
    //     cout << "\n";
    // }
    int ans = *min_element(dis[N - 1].begin(), dis[N - 1].end());
    return ans == inf ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
