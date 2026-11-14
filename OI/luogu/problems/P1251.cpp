// Problem : P1251 餐巾计划问题 https://www.luogu.com.cn/problem/P1251
// Time    : 2026-11-14 17:13:13
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
void init() {}int N;                  // 点数（0..N-1）
vector<vi> e;           // e[u] = {边号, ...}
vi to, preEdge;         // to[i] = 边 i 的终点；preEdge[v] = 走到 v 用的边号
vll cap, cap0;          // cap[i] = 剩余容量。**用 ll**：P1251 里 Σr_i 能到 2×10^10，int 装不下
vll cost, dis;          // cost[i] = 边 i 的单位费用；dis[v] = 当前增广路上的最短费用

void MCMF_init(int n) {
    N = n;
    e.assign(n, {});
    to.clear(), cap.clear(), cost.clear();
}

// 加一条 u→v 容量 c、单位费用 w 的边；返回边号（方案还原时用它查 cap）
// c 也是 ll：容量别在签名上收窄
int addEdge(int u, int v, ll c, ll w) {
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
        ll lim = cap[preEdge[t]];
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vll r(n), a(5);
    cin >> r >> a;
    int s = 0, t = 2 * n + 1, NN = t + 1;
    MCMF_init(NN);
    for (int i = 1; i <= n; i++) {
        ll x = r[i - 1];
        addEdge(s, i, INF, a[0]);
        addEdge(i, t, x, 0);
        addEdge(s, i + n, x, 0);
        if (i < n) addEdge(i + n, i + n + 1, INF, 0);
        if (i + a[1] <= n) addEdge(i + n, i + a[1], INF, a[2]);
        if (i + a[3] <= n) addEdge(i + n, i + a[3], INF, a[4]);
    }
    return MCMF(s, t).second;
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
