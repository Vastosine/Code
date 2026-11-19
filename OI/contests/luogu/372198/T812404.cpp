// Problem : T812404 [ICPC 2026 Nanchang I] Journey of GCD https://www.luogu.com.cn/problem/T812404?contestId=372198
// Time    : 2026-11-19 13:00:05
#include <algorithm>
#include <iostream>
#include <set>
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
vi primes, pre;
vector<bool> is;
void sieve(int n) {
    is.assign(n + 1, 1);
    pre.assign(n + 1, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i), pre[i] = i;
        for (int p : primes) {
            if (1ll * i * p > n) break;
            is[i * p] = 0;
            pre[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

void init() {
    sieve(1e6);
}

vi f(int x) {
    int X = x;
    vector<pii> lst;
    while (x > 1) {
        if (!lst.empty() && lst.back().first == pre[x]) lst.back().second++;
        else lst.push_back({pre[x], 1});
        x /= pre[x];
    }
    vi o(1, X);
    set<int> vis;
    vis.insert(X);
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (auto &[p, c] : lst) {
            if (int v = u / p; u % p == 0 && vis.find(v) == vis.end()) {
                vis.insert(v);
                o.push_back(v);
            }
        }
    }
    return vi(vis.begin(), vis.end());
}



auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    int N = 1e6;
    int D = __lg(N) + 1;
    vector<vi> fa(N + 1, vi(D + 1)), e(N + 1);
    fa[1][0] = 1;
    for (int x : a) {
        vi lst = f(x);
        for (int i = 1; i < (int) lst.size(); i++) {
            fa[lst[i]][0] = max(fa[lst[i]][0], lst[i - 1]);
        }
    }
    for (int d = 0; d < D; d++) {
        for (int u = 1; u <= N; u++) {
            fa[u][d + 1] = fa[fa[u][d]][d];
        }
    }
    // for (int i = 1; i <= 100; i++) cout << fa[i][0] << "\n";
    vi dep(N + 1), o(1, 1);
    dep[1] = 1;
    for (int i = 2; i <= N; i++) {
        e[i].push_back(fa[i][0]);
        e[fa[i][0]].push_back(i);
    }
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v);
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
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(a[u - 1], a[v - 1]) << "\n";
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
