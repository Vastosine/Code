// Problem : C. Fools and Roads https://codeforces.com/problemset/problem/191/C
// Time    : 2026-11-09 15:14:19
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

// f[u]: the value of edge from u to fa[u]
// p = lca(u, v), f[p] -= 2, f[u]++, f[v]++;
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<vector<pii>> e;
    vi f, o(1, 1), id, dep;
    vector<vi> fa;
    assign(n + 1, e, f, id, dep);
    const int D = 20;
    fa.assign(n + 1, vi(D + 1));
    for (int i = 1; i < n; i++) {
        int u, v, w = i - 1;
        cin >> u >> v;
        e[u].push_back({v, w}); e[v].push_back({u, w});
    }
    fa[1][0] = 1, dep[1] = 1, id[1] = -1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (auto &[v, w] : e[u]) {
            if (!fa[v][0]) fa[v][0] = u, o.push_back(v), id[v] = w, dep[v] = dep[u] + 1;
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
            int nxt = fa[u][d];
            if (dep[nxt] >= dep[v]) u = nxt;
        }
        if (u == v) return u;
        for (int d = D; ~d; d--) {
            int nu = fa[u][d], nv = fa[v][d];
            if (nu != nv) u = nu, v = nv;
        }
        return fa[u][0];
    };
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int x = LCA(u, v);
        f[x] -= 2;
        f[u]++;
        f[v]++;
    }
    vi ans(n - 1);
    for (int i = n - 1; i; i--) {  // ignore root
        int u = o[i];
        for (auto &[v, w] : e[u]) {
            if (dep[v] > dep[u]) f[u] += f[v];
        }
        ans[id[u]] = f[u];
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
