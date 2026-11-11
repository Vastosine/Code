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
vi vis;
vll dis;
int n;

void Dijkstra(int s) {
    vis.assign(n + 1, 0);
    dis.assign(n + 1, 1ll << 60);
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
            }
        }
    }
}