// Problem : F. Maximum White Subtree https://codeforces.com/problemset/problem/1324/F
// Time    : 2026-11-09 12:41:29
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
vector<vi> e;
vi a, f, g, vis, vis2;
void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

// State: f[u]: 1 as root, u subtree's max value
// Transfer: f[u] = a[i] + sum{ max(f[v], 0) }, v in son[u], a[i] = 1 -> white -1 -> black
int dfs1(int u = 1) {
    vis[u] = 1;
    f[u] = a[u];
    for (int v : e[u]) {
        if (!vis[v]) {
            f[u] += max(dfs1(v), 0);
        }
    }
    return f[u];
}

// Calculate: ans[u] = f[u] + max(0, father's stream), stream to son[x] = ans[u] - max(0, f[son[x]])
// Complexity: 2e5 * 2
void dfs2(int u = 1, int stream = 0) {
    vis2[u] = 1;
    g[u] = f[u] + max(0, stream);
    for (int v : e[u]) {
        if (!vis2[v]) {
            dfs2(v, g[u] - max(0, f[v]));
        }
    }
}
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    assign(n + 1, e, a, f, g, vis, vis2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = a[i] * 2 - 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }
    dfs1();
    dfs2();
    for (int i = 1; i <= n; i++) cout << g[i] << " ";
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
