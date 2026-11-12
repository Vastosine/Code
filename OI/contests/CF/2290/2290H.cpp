// Problem : H. Extra Road https://codeforces.com/contest/2290/problem/H
// Time    : 2026-11-12 22:35:23
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<vi> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    vi o(1, 1), fa(n + 1), f(n + 1), g(n + 1), siz(n + 1);
    fa[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!fa[v]) fa[v] = u, o.push_back(v);
        }
    }
    int ans = 0;
    for (int i = n - 1; i; i--) {
        int u = o[i];
        siz[u] = 1;
        for (int v : e[u]) {
            if (fa[v] == u) {
                siz[u] += siz[v];
                if (siz[v] > f[u]) g[u] = f[u], f[u] = siz[v];
                else if (siz[v] > g[u]) g[u] = siz[v];
            }
        }
        if (u != 1) ans = max(ans, g[u]);
    }
    vi rs;
    for (int v : e[1]) rs.push_back(siz[v]);
    Sort(rs);
    if (rs.size() > 2) ans = max(ans, rs[rs.size() - 3]);
    return n - ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
