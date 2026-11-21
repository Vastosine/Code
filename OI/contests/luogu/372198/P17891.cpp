// Problem : P17891 [ICPC 2026 Nanchang I] Eating Cherries https://www.luogu.com.cn/problem/P17891?contestId=372198
// Time    : 2026-11-20 11:48:59
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
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
    int n, m;
    cin >> n >> m;
    int M = 1 << m;
    vector<vi> e(n + 1), s(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            a[i] |= (1 << (x - 1));
        }
    }
    vi o(1, 1), fa(n + 1, 0), ans(n + 1);
    vi pre(n + 1, 0); 
    pre[1] = a[1]; 
    fa[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!fa[v]) fa[v] = u, o.push_back(v), s[u].push_back(v), pre[v] = pre[u] | a[v];
            // if (!fa[v]) fa[v] = u, o.push_back(v), s[u].push_back(v);
        }
    }
    vector<vi> g(n + 1, vi(M, 0));
    int deg1 = 0, base = 0;
    for (int u = 1; u <= n; u++) {
        if (e[u].size() > 1) base |= a[u];
        else deg1++;
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        if (s[u].empty()) g[u][a[u]] = 1;
        for (int v : s[u]) {
            for (int j = 0; j < M; j++) {
                g[u][j | a[u]] += g[v][j];
            }
        }
    }
     for (int i = 0; i < n; i++) {
        int u = o[i];
        if (fa[u] != u) {
            vi og = g[fa[u]];
            for (int j = 0; j < M; j++) og[a[fa[u]] | j] -= g[u][j];
            for (int j = 0; j < M; j++) g[u][a[u] | j] += og[j];
        }
        vi hist = g[u];
        int L = deg1 - ((int) e[u].size() == 1 ? 1 : 0);
        int x = base | ((int) e[u].size() == 1 ? a[u] : 0);
        if (u != 1 && (int) e[u].size() == 1) hist[a[u]]--;        // u 变根，自己不再是叶子
        if (u != 1 && (int) e[1].size() == 1) hist[pre[u]]++;      // 原来的根 1 变回叶子

        assert(accumulate(hist.begin(), hist.end(), 0ll) == L);

        int res = inf;
        for (int j = 0; j < M; j++) {
            if ((j & x) != x) continue;
            res = min(res, L - hist[j]);
        }
        ans[u] = res < 0 ? 0 : res;
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
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
