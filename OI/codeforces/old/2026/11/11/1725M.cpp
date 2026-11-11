// Problem : M. Moving Both Hands https://codeforces.com/problemset/problem/1725/M
// Time    : 2026-11-11 09:20:39
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
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

// e1 : positive graph
// e2 : negtive graph
// run Dijkstra on e1 and then remain dis to run Dijkstra on e2
auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> e[2];
    vll dis;
    vi vis;
    assign(n + 1, e[0], e[1]);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        e[0][u].push_back({v, w});
        e[1][v].push_back({u, w});
    }
    auto Dij = [&] (int mode) {
        priority_queue<pll> q;
        vis.assign(n + 1, 0);
        if (mode == 0) {
            q.push({0, 1});
            dis.assign(n + 1, INF);
            dis[1] = 0;
        } else {
            for (int u = 1; u <= n; u++) {
                if (dis[u] != INF) q.push({-dis[u], u});
            }
        }
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &[v, w] : e[mode][u]) {
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.push({-dis[v], v});
                }
            }
        }
    };
    Dij(0);
    Dij(1);
    for (int i = 2; i <= n; i++) cout << (dis[i] == INF ? -1 : dis[i]) << " ";
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
