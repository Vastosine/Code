// Problem : E. Vasya and a Tree https://codeforces.com/problemset/problem/1076/E
// Time    : 2026-11-09 19:14:04
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

int n;
vector<vi> e;
vector<vector<pii>> op;
vll ans, dep, delta;
void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

void dfs(int u = 1, int depth = 1, ll cur = 0) {
    dep[u] = depth;
    for (auto &[x, d] : op[u]) {
        delta[dep[u]] += x;
        if (d + dep[u] + 1 <= n) delta[d + dep[u] + 1] -= x; 
    }
    cur += delta[dep[u]];
    ans[u] = cur;
    for (int v : e[u]) {
        if (!dep[v]) {
            dfs(v, depth + 1, cur);
        }
    }
    for (auto &[x, d] : op[u]) {
        delta[dep[u]] -= x;
        if (d + dep[u] + 1 <= n) delta[d + dep[u] + 1] += x; 
    }
}

// State: delta[d]: current subtree's delta with depth of d
//        cur: current vertice's value
// Transfer: in: cur/delta[dep[u]] += x[i], delta[dep[u] + d[i] + 1] -= x[i], for every i operated at u
//           out: drawback the operation when in
// Complexity: O(n + m)
// Border: dep[1] = 1, delta[x] no operation when x > maxdep
auto Main([[maybe_unused]] int C = 0) {
    cin >> n;
    assign(n + 1, e, op, ans, dep, delta);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }
    int q;
    cin >> q;
    while (q--) {
        int v, d, x;
        cin >> v >> d >> x;
        op[v].push_back({x, d});
    }
    dfs();
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
