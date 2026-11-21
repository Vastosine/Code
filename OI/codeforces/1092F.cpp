// Problem : F. Tree with Maximum Cost https://codeforces.com/problemset/problem/1092/F
// Time    : 2026-11-21 09:32:54
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
    int n;
    cin >> n;
    vector<vi> e;
    vi dep, fa, siz;
    vll sum, f, res, a;
    assign(n + 1, e, siz, dep, fa, sum, f, res, a);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    vi o(1, 1);
    dep[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) {
                dep[v] = dep[u] + 1;
                fa[v] = u;
                o.push_back(v);
            }
        }
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        sum[u] += a[u];
        siz[u] += 1;
        if (fa[u]) {
            siz[fa[u]] += siz[u];
            sum[fa[u]] += sum[u];
            f[fa[u]] += f[u] + sum[u];
        }
    }
    for (int u : o) {
        if (u == 1) res[u] = f[u];
        else {
            int p = fa[u];
            ll stream = (res[p] - f[u] - sum[u]) + (sum[1] - sum[u]);
            res[u] = stream + f[u];
        }
    }
    return *max_element(res.begin() + 1, res.end());
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
