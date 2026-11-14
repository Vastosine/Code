#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;

// ── 什么时候用这个文件 ────────────────────────────────────────────
// 最小费用最大流（MCMF）。建图 → 调 MCMF(s, t) → 拿 {最大流, 最小费用}。
//
// 存储方式是「边集数组 + 邻接表存边号」：e[u] 存的是边号，不是终点。
// 一条边和它的反向边边号只差 1（i 与 i^1），所以反向边永远是 c[i ^ 1]。
// 这个位运算不是技巧，是**必须**遵守的约定：addEdge 里两条边是连着 push 的。
//
// 为什么用 SPFA 找增广路，不用 Dijkstra：
//   第一次增广后，反向边带着负费用进入残余图，原图即使全非负，Dijkstra 也会错。
//   两条出路：(a) 本文件，SPFA 容忍负边；(b) Dijkstra + 势能（Johnson 重标号）。
//   本文件选 (a)，因为短。
//
// 复杂度：O(flow · V · E)。flow 大（上万）且原图费用非负时换成势能 Dijkstra，
// 否则会被卡。网络流 24 题的量级用这里够。
//
// 最大费用最大流：调 MCMF(s, t, -1)，不要另写一份。同一个问题问两遍时的标准写法：
//     MCMF_init(N); /* 加边 */ MCMF_snapshot();
//     ll lo = MCMF(s, t,  1).second;
//     MCMF_reset();                       // 只复原容量，边表不用重建
//     ll hi = MCMF(s, t, -1).second;
// 恢复容量是必须的：第一遍跑完后 cap[] 是残余网络，不是原图。
// ─────────────────────────────────────────────────────────────────

int N;                  // 点数（0..N-1）
vector<vi> e;           // e[u] = {边号, ...}
vi to, cap, preEdge;    // to[i] = 边 i 的终点；cap[i] = 剩余容量；preEdge[v] = 走到 v 用的边号
vll cost, dis;          // cost[i] = 边 i 的单位费用；dis[v] = 当前增广路上的最短费用
vi cap0;                // 建图时的原始容量，MCMF_reset() 用来复原

void MCMF_init(int n) {
    N = n;
    e.assign(n, {});
    to.clear(), cap.clear(), cost.clear();
}

// 加一条 u→v 容量 c、单位费用 w 的边；返回边号（方案还原时用它查 cap）
int addEdge(int u, int v, int c, ll w) {
    int id = (int)to.size();
    e[u].push_back(id);
    to.push_back(v), cap.push_back(c), cost.push_back(w);
    e[v].push_back(id + 1);
    to.push_back(u), cap.push_back(0), cost.push_back(-w);
    return id;
}

// 同一个问题要问「最小费用」和「最大费用」两遍时：加完边存一份，跑第二遍前复原。
// 只复原容量就够，不必重建边表。
void MCMF_snapshot() { cap0 = cap; }
void MCMF_reset() { cap = cap0; }

// 返回 {flow, totalCost}。dir = 1 求最小费用，dir = -1 求最大费用（内部把费用取反算，
// 返回的 totalCost 仍是原始费用的和，可以直接输出）。
// 图里存在从 s 可达的负环时返回 {-1, -1}（此时无最小费用流）。
pll MCMF(int s, int t, int dir = 1) {
    const ll INF = 1ll << 60;
    ll flow = 0, ans = 0;
    while (true) {
        dis.assign(N, INF);
        preEdge.assign(N, -1);          // 用 -1 而不是 0：边号 0 是合法边
        vi cnt(N, 0), inq(N, 0);
        queue<int> q;

        dis[s] = 0, q.push(s), inq[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i : e[u]) {
                int v = to[i];
                if (cap[i] <= 0) continue;           // 残余容量为 0 的边不能走
                if (ll nd = dis[u] + cost[i] * dir; nd < dis[v]) {
                    dis[v] = nd;
                    preEdge[v] = i;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= N) return {-1, -1};   // 最短路 ≥ N 条边 ⟹ 负环
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        if (preEdge[t] == -1) break;                  // 没有增广路 ⟹ 已经最大流

        // lim 直接取路径上第一条边的容量当初始值：不依赖 INT_MAX 之类需要
        // 额外 include 的宏。有人会把本文件整段粘进自己的代码，那时缺 <climits> 就 CE。
        int lim = cap[preEdge[t]];
        for (int v = t; v != s; v = to[preEdge[v] ^ 1]) lim = min(lim, cap[preEdge[v]]);
        for (int v = t; v != s; v = to[preEdge[v] ^ 1]) {
            cap[preEdge[v]] -= lim;
            cap[preEdge[v] ^ 1] += lim;
            ans += 1ll * lim * cost[preEdge[v]] * dir;
        }
        flow += lim;
    }
    return {flow, ans * dir};                         // 把 dir 的符号翻回来
}

// ── 方案还原 ──────────────────────────────────────────────────────
// addEdge 的返回值就是正向边号 id。跑完之后：
//   cap[id] == 0        ⟹ 这条边用满了（容量 1 的边就是「被选中」）
//   cap[id ^ 1]         ⟹ 已经流过去的量
// 不要扫「对方」的邻接表去找反向边——那是同一件事的两套判据，写反过不止一次。
//
// 稀疏图/多测注意：MCMF_init 会清空边，但 e 里的 vector 也会被重置；每个测试点都要重建。
