// Problem : E. A and B and Lecture Rooms https://codeforces.com/problemset/problem/519/E
// Time    : 2026-11-10 08:52:25
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

// ans = n when u == v
// x = LCA(u, v), d = dis(u, v), h = d / 2 - 1
// ans = 0 when d is odd
// when d is even and positive: (f(u, k) is the k-th parent of u)
//   if dep[u] == dep[v], ans = n - siz[f(u, h)] - siz[f(v, h)]
//   else, ans = siz[f(u, h + 1)] - siz[f(u, h)], (dep[u] > dep[v]);
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    const int D = __lg(n) + 1;
    vector<vi> e, f(n + 1, vi(D + 1));
    vi dep, siz;
    assign(n + 1, e, dep, siz);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    f[1][0] = 1, dep[1] = 1;
    vi o(1, 1);
    for (int i = 0; i < n; i++) {
        int u = o[i];
        siz[u] = 1;
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v), f[v][0] = u;
        }
    }
    for (int d = 1; d <= D; d++) {
        for (int u = 1; u <= n; u++) {
            f[u][d] = f[f[u][d - 1]][d - 1];
        }
    }
    for (int i = n - 1; i; i--) {
        int u = o[i];
        siz[f[u][0]] += siz[u];
    }
    auto LCA = [&] (int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int d = D; ~d; d--) {
            int nu = f[u][d];
            if (dep[nu] >= dep[v]) u = nu;
        }
        if (u == v) return u;
        for (int d = D; ~d; d--) {
            int nu = f[u][d], nv = f[v][d];
            if (nu != nv) u = nu, v = nv;
        }
        return f[u][0];
    };
    auto get_dis = [&] (int u, int v, int x) {
        return dep[u] + dep[v] - 2 * dep[x];
    };
    auto fa = [&] (int u, int x) {
        int d = 0;
        while (x) {
            if (x & 1) u = f[u][d];
            d++;
            x /= 2;
        }
        return u;
    };
    auto F = [&] (int u, int v) {
        if (u == v) return n;
        int x = LCA(u, v), dis = get_dis(u, v, x), h = dis / 2 - 1;
        if (dis & 1) return 0;
        if (dep[u] == dep[v]) return n - siz[fa(u, h)] - siz[fa(v, h)];
        if (dep[u] < dep[v]) swap(u, v);
        return siz[fa(u, h + 1)] - siz[fa(u, h)];
        
    };
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << F(u, v) << "\n";
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
