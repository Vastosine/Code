// Problem : A. The Fair Nut and the Best Path https://codeforces.com/problemset/problem/1083/A
// Time    : 2026-11-09 13:22:16
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

// State: f[u], g[u]: 1 as root, subtree u's max and vice max oil can be obtain, f contains u
// Transfer: f[u] = a[u] + max(0, max(f[v] - w[u, v]))
// Complexity: O(n)
// Calculate: max(f[u] + g[u])
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vll a(n + 1);
    vector<vector<pair<ll, ll>>> e(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w}); 
        e[v].push_back({u, w});
    }
    vll f(n + 1), g(n + 1);
    vi order(1, 1), fa(n + 1);
    fa[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = order[i];
        for (auto &[v, w] : e[u]) {
            if (!fa[v]) fa[v] = u, order.push_back(v);
        }
    }
    ll ans = NEG;
    for (int i = n - 1; ~i; i--) {
        int u = order[i];
        for (auto &[v, w] : e[u]) {
            if (fa[v] == u) {
                ll add = f[v] - w;
                if (add > f[u]) g[u] = f[u], f[u] = add;
                else if (add > g[u]) g[u] = add;
            }
        }
        f[u] += a[u];
        ans = max(ans, f[u] + g[u]);
    }
    return ans;
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
