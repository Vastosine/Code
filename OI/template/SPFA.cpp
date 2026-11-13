#include <queue>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

// ── 什么时候用这个文件 ────────────────────────────────────────────
// 只在两种情况下用 SPFA：
//   1. 图里有**负权边**（Dijkstra 直接错）
//   2. 要**判负环**
// 非负权 + 单源最短路 → 一律 Dijkstra.cpp，别用这里。
//
// SPFA 最坏 O(n·m)，出题人会专门造数据卡它（网格图、菊花图最常见）。
// 负权但 n·m 撑不住时：改成 Bellman-Ford（同样 O(n·m) 但没有入队风暴），
// 或者用 Johnson 重标号 + Dijkstra。
//
// 差分约束（x_v ≥ x_u + w）→ 把 w 全部取反、跑本函数：
//   返回 false ⟺ 有正环 ⟺ 无解；否则 x_v = -dis[v]。
// ─────────────────────────────────────────────────────────────────

// e[u] = {{v, w}, ...}；w 用 ll，不要塞进 pair<int,int>（会静默窄化）
vector<vector<pair<int, ll>>> e;
vi pre;                     // pre[v] = 最短路上 v 的前一个点，倒序回溯
int n;
vll dis;
const ll INF = 1ll << 60;

// 返回 false ⟺ 存在从 s 可达的负环（此时 dis 无意义）
bool SPFA(int s) {
    dis.assign(n + 1, INF);
    pre.assign(n + 1, 0);
    vi cnt(n + 1, 0);       // cnt[v] = 当前最短路走到 v 用了几条边
    vi inq(n + 1, 0);       // 在不在队列里 —— 少了这个，同一个点会被反复塞进去
    queue<int> q;

    dis[s] = 0, q.push(s), inq[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto &[v, w] : e[u]) {
            if (ll nd = dis[u] + w; nd < dis[v]) {
                dis[v] = nd;
                pre[v] = u;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;  // 最短路走了 ≥ n 条边 ⟹ 重复顶点 ⟹ 负环
                if (!inq[v]) q.push(v), inq[v] = 1;
            }
        }
    }
    return true;
}
