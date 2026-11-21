// Problem : P3047 [USACO12FEB] Nearby Cows G https://www.luogu.com.cn/problem/P3047
// Time    : 2026-11-21 09:49:27
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
    int n, k;
    cin >> n >> k;
    vector<vi> e, f(n + 1, vi(k + 1)), g(n + 1, vi(k + 1));
    vi vis, o(1, 1), a, fa, res;
    assign(n + 1, e, vis, a, fa, res);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
    vis[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!vis[v]) vis[v] = 1, o.push_back(v), fa[v] = u;
        }
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        f[u][0] = a[u];
        for (int v : e[u]) {
            for (int j = 0; j < k; j++) {
                f[u][j + 1] += f[v][j];
            }
        }
    }
    for (int u : o) {
        if (u == 1) g[u] = f[u];
        else {
            g[u][0] = a[u];
            for (int j = 0; j < k; j++) {
                int add = g[fa[u]][j];
                if (j) add -= f[u][j - 1];
                g[u][j + 1] = f[u][j + 1] + add;
            }
        }
        for (int x : g[u]) res[u] += x;
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << "\n";
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
