// Problem : E. A and B and Lecture Rooms https://codeforces.com/problemset/problem/519/E
// Time    : 2026-11-09 20:45:48
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

// the answer is 0 when dis(u, v) is odd
// ans = n when u == v ? (maybe impossibly appear)
// when dis(u, v) is even:
//   h = dis / 2 - 1, 
//   x = LCA(u, v)
//   fa(u, k) = the k-th parent of u
//   if dep[u] == dep[v], ans = n - siz[fa(u, h)] - siz[fa(v, h)]
//   else ans = siz[fa(u, h + 1)] - siz[fa(u, h)], (dep[u] > dep[v])
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    const int D = __lg(n) + 1;
    vector<vi> e, fa(n + 1, vi(D + 1));
    vi dep, siz;
    assign(n + 1, dep, siz, e);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    vi o(1, 1);
    dep[1] = 1, fa[1][0] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        siz[u] = 1;
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v), fa[v][0] = u;
        }
    }
    for (int i = n - 1; i; i--) {
        int u = o[i];
        siz[fa[u][0]] += siz[u];
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
    auto dis = [&] (int u, int v, int x) {
        return dep[u] + dep[v] - 2 * dep[x];
    };
    auto f = [&] (int u, int x) {
        int d = 0;
        while (x) {
            if (x & 1) u = fa[u][d];
            x /= 2;
            d++;
        }
        return u;
    };
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int x = LCA(u, v);
        int d = dis(u, v, x);
        int h = d / 2 - 1;
        int ans = 0;
        if (!(d & 1)) {
            if (dep[u] == dep[v]) {
                ans = n - siz[f(u, h)] - siz[f(v, h)];
            } else {
                if (dep[u] < dep[v]) swap(u, v);
                ans = siz[f(u, h + 1)] - siz[f(u, h)];
            }
        }
        cout << ans << "\n";
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
