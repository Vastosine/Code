// Problem : G1. Passable Paths (easy version) https://codeforces.com/problemset/problem/1702/G1
// Time    : 2026-11-09 15:51:19
#include <iostream>
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

// find the ends of the path a, b
// one(a) end must be the deepest, the other(b) will be the furthest from a
// Verify each queried vertice whether fits dis(a, v) + dis(v, b) = dis(a, b)
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    const int D = 20;
    vector<vi> e, fa(n + 1, vi(D + 1));
    vi dep, o(1, 1);
    assign(n + 1, e, dep);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    fa[1][0] = 1; dep[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, fa[v][0] = u, o.push_back(v);
        }
    }
    for (int d = 1; d <= D; d++) {
        for (int u = 1; u <= n; u++) {
            fa[u][d] = fa[fa[u][d - 1]][d - 1];
        }
    }
    auto LCA = [&] (int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int d = D; ~d; d--) {
            int nu = fa[u][d];
            if (dep[nu] >= dep[v]) u = nu;
        }
        if (u == v) return u;
        for (int d = D; ~d; d--) {
            int nu = fa[u][d], nv = fa[v][d];
            if (nu != nv) u = nu, v = nv;
        }
        return fa[u][0];
    };
    auto dis = [&] (int u, int v) {
        int x = LCA(u, v);
        return dep[u] + dep[v] - 2 * dep[x];
    };
    int Q;
    cin >> Q;
    const string OUT[2] = {"NO", "YES"};
    while (Q--) {
        int m;
        cin >> m;
        vi a(m);
        cin >> a;
        int p = 0;
        for (int u : a) {
            if (dep[u] > dep[p]) p = u;
        }
        int q = p, s = 0;
        for (int u : a) {
            int ns = dis(p, u);
            if (ns > s) q = u, s = ns;
        }
        bool ans = 1;
        for (int u : a) {
            if (dis(u, p) + dis(u, q) != dis(p, q)) {
                ans = 0;
                break;
            }
        }
        cout << OUT[ans] << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
     init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
