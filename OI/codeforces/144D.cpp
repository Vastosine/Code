// Problem : D. Missile Silos https://codeforces.com/problemset/problem/144/D
// Time    : 2026-11-11 09:52:08
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

// Undirected graph
// Dijkstra for s
// calculate count of dis[u] == l 
// and sum of (x > l * 2) + (x >= l * 2) - (dis[u] >= l) - (dis[v] >= l), x = dis[u] + dis[v] + w;
auto Main([[maybe_unused]] int C = 0) {
    int n, m, s, l;
    cin >> n >> m >> s;
    vector<vector<pii>> e;
    vll dis(n + 1, INF);
    vi vis;
    assign(n + 1, e, vis);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w}); e[v].push_back({u, w});
    }
    cin >> l;
    dis[s] = 0;
    priority_queue<pll> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                q.push({-dis[v], v});
            }
        }
    }
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        ans += dis[u] == l;
        for (auto &[v, w] : e[u]) {
            if (v < u) continue;
            ll x = dis[u] + dis[v] + w;
            ans += (x > l * 2) + (x >= l * 2) - (dis[u] >= l) - (dis[v] >= l);
        }
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
