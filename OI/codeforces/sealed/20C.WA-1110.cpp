// Problem : C. Dijkstra? https://codeforces.com/problemset/problem/20/C
// Time    : 2026-11-10 19:06:44
#include <iostream>
#include <queue>
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

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> e;
    vi vis, pre;
    vll dis(n + 1, INF);
    assign(n + 1, e, vis, pre);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
    }
    priority_queue<pii> q;
    q.push({0, 1});
    dis[1] = 0;
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : e[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = u;
            }
            q.push({-dis[v], v});
        }
    }
    if (dis[n] == INF) return cout << -1 << "\n", 0;
    vi ans;
    int ed = n;
    while (ed) {
        ans.push_back(ed);
        ed = pre[ed];
    }
    while (!ans.empty()) {
        cout << ans.back() << " ";
        ans.pop_back();
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
