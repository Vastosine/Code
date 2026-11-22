// Problem : E. The Problem from Silach https://codeforces.com/contest/2289/problem/E
// Time    : 2026-11-22 17:05:15
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
    int N = n * 2;
    vector<vi> son;
    vi mn, mx, dep;
    assign(N, son, mn, mx, dep);
    const int D = __lg(n) + 1;
    vector<vi> fa(N, vi(D + 1));
    int s = n * 2 - 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        son[i + n] = {u, v};
        fa[u][0] = fa[v][0] = i + n;
    }
    fa[s][0] = s;
    for (int d = 0; d < D; d++) {
        for (int u = 1; u < N; u++) {
            fa[u][d + 1] = fa[fa[u][d]][d];
        }
    }
    vi o(1, s);
    dep[s] = 1;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : son[u]) {
            dep[v] = dep[u] + 1;
            o.push_back(v);
        }
    }
    for (int i = (int) o.size() - 1; ~i; i--) {
        int u = o[i];
        if (u <= n) mn[u] = mx[u] = u;
        else {
            int ls = son[u][0], rs = son[u][1];
            mn[u] = min(mn[ls], mn[rs]);
            if (mx[ls] > mx[rs]) swap(ls, rs);
            // mx[u] = min({mx[ls] + k - 1, mx[rs] + k - 1, max(mx[ls], mx[rs])});
        }
    }
    cout << mx << "\n";
    return 0;
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
