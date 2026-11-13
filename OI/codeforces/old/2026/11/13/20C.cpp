// Problem : C. Dijkstra? https://codeforces.com/problemset/problem/20/C
// Time    : 2026-11-13 09:31:48
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// e is given by main: e[u] = {{v, w}, ...}; w must fit int (switch to pll for 1e18 weights)
vector<vector<pii>> e;
vi vis, pre;
vll dis;
int n;
const ll INF = 1ll << 60;

void Dijkstra(int s) {
    pre.assign(n + 1, 0);
    vis.assign(n + 1, 0);
    dis.assign(n + 1, INF);
    dis[s] = 0;
    priority_queue<pll> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
            auto nd = w + dis[u];
            if (nd < dis[v]) {
                dis[v] = nd;
                q.push({-nd, v});
                pre[v] = u;
            }
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    e.assign(n + 1, {});
    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[u].push_back({v, w}); e[v].push_back({u, w});
    }
    Dijkstra(1);
    if (dis[n] == INF) cout << -1;
    else {
        vi ans;
        for (int u = n; u; u = pre[u]) {
            ans.push_back(u);
        }
        for (int i = (int) ans.size() - 1; ~i; i--) cout << ans[i] << " ";
    }
}