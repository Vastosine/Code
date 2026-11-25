// reroot.cpp -- 换根 DP 骨架
// 归纳自 2026-11-21：P3478 / CF1092F 标量档，P17891 / P3047 整表档
//
// ---------------------------------------------------------------- 三 档
// 按「换根时要传下去的东西」分类，这决定了实现方式：
//
//   ① 标量            res[v] = res[u] + delta(u, v)
//                    逆序求 down，正序推 all，不需要表
//
//   ② 整表 + 索引平移   g[v][x] = f[v][x] + g[u][T(x)] - f[v][T2(x)]
//                    三件事按顺序：在父亲的坐标系里减 → 平移 → 加自己那一圈
//                    T(x)   = 往父亲走一步，路径量怎么变（距离 +1；OR 加 a[fa]）
//                    T2(x)  = 「父亲的一格」对应「自己的前一格 / 前两格」
//                    「自己那一圈」f[v][x] 从来不在父亲的表里，必须显式加
//
//   ③ 不可逆           max / min / mex / 不同值个数：减法不存在
//                    对每个点维护所有儿子的 top-2（见 Top2），
//                    或者预处理 pre[i] / suf[i] 前缀后缀合并
//
// ---------------------------------------------------------- 五 种 失 效
//   叶子判定   有根树的叶子 = 没有儿子（s[u].empty()），不是度 1
//   L 用错     根不算叶子：L = 度1点数 - (根是度 1 ? 1 : 0)
//   索引平移   见 ②。忘掉就是负下标 / 少算 / 重复算，而且都不崩
//   修正写回   临时修正只作用于「当前根的答案」，不许写回要传给儿子的表
//   叶子集变   根换了，谁算叶子也跟着换 —— 原来的根可能变回叶子，
//              路径量要用 pre[u]（根到 u 的前缀）补回去
//
// ------------------------------------------------------ 现 成 的 式 子
// 档① 点数版  P3478      res[v] = res[u] + n - 2 * siz[v]
//     权值版  CF1092F    res[v] = res[u] + S - 2 * sub[v]      S = Σa, sub = 子树权和
// 档② 距离类  P3047      g[v][k] = f[v][k] + g[u][k-1] - f[v][k-2]    k < 2 时末项不存在
//     OR 类   P17891     og = g[u]; og[a[u]|j] -= f[v][j]; g[v][a[v]|x] += og[x]
// 档③ 最大值  top2.best(child_value) 去掉某个儿子之后的最大值
//
// ------------------------------------------------------------ 用 法
//   Reroot R; R.init(n);
//   for (...) R.addEdge(u, v);
//   R.build(1);
//   R.down([&](int u) { /* 逆序：v 的 s[v] / f[v] 一定已经算好 */ });
//   R.up  ([&](int u) { /* 正序：g[fa[u]] 一定已经算好 */ });
//
// 注意 up 里不要写 g[u]，要写 g[u] 的「新表」；也不要覆盖 f[u]。
// 判空：n = 1、链、菊花、n = 2（两个点都是度 1）各测一遍。

#include <vector>
#include <cassert>

using namespace std;
using ll = long long;
using vi = vector<int>;

// 建树：迭代，无递归。fa[root] = 0，未访问 = -1。
// 不用 dep == 0 当访问标记 —— 一个数组一个语义，出问题时才知道是哪个坏了。
struct Reroot {
    int n = 0, root = 1;
    vector<vi> e, s;   // 无根邻接表 / 有根儿子表
    vi fa, dep, o;     // 父亲 / 深度(根 = 1) / BFS 序（父亲一定在儿子前面）

    void init(int n0) {
        n = n0;
        e.assign(n + 1, vi());
        s.assign(n + 1, vi());
        fa.assign(n + 1, -1);
        dep.assign(n + 1, 0);
        o.clear();
    }

    void addEdge(int u, int v) { e[u].push_back(v), e[v].push_back(u); }

    void build(int rt = 1) {
        root = rt;
        fa.assign(n + 1, -1);
        dep.assign(n + 1, 0);
        for (int u = 1; u <= n; u++) s[u].clear();
        o.clear(), o.push_back(rt);
        fa[rt] = 0, dep[rt] = 1;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int v : e[u])
                if (fa[v] == -1) fa[v] = u, dep[v] = dep[u] + 1, s[u].push_back(v), o.push_back(v);
        }
        assert((int) o.size() == n);   // 不是连通树说明调用方给错了
    }

    bool isLeaf(int u) const { return s[u].empty(); }        // 有根意义下的叶子
    int degree(int u) const { return (int) e[u].size(); }    // 无根意义下的度数

    // ---- 儿子表：两种表示，按 n 选 ----
    //
    // 实测 1e6 随机树（本地，9 轮交错取最小值，P3478 端到端）：
    //   不建儿子表                                   基准
    //   vector<vi> + reserve + push_back             +106 ms
    //   CSR（cstart / cadj，两次前缀和，一次大分配）   +36 ms
    //
    // vector<vi> 的代价是 1e6 个 vector 头（24 MB）和 1e6 次 malloc。
    // n <= 2e5 时随便用；n >= 1e6 且卡 1 s，必须换 CSR。
    vi cstart, cadj;
    void buildChildrenCSR() {
        cstart.assign(n + 2, 0);
        for (int v = 1; v <= n; v++)
            if (v != root) cstart[fa[v] + 1]++;
        for (int u = 1; u <= n; u++) cstart[u + 1] += cstart[u];
        cadj.assign(n > 1 ? n - 1 : 1, 0);
        vi cur(cstart.begin(), cstart.end());
        for (int v = 1; v <= n; v++)
            if (v != root) cadj[cur[fa[v]]++] = v;
        // 遍历 u 的儿子： for (int i = cstart[u]; i < cstart[u + 1]; i++) { int v = cadj[i]; ... }
    }

    // 反序：儿子先于父亲。向下 DP / 子树统计
    template<typename F> void down(F f) {
        for (int i = (int) o.size() - 1; ~i; i--) f(o[i]);
    }
    // 正序：父亲先于儿子。换根
    template<typename F> void up(F f) {
        for (int u : o) f(u);
    }
};

// 档③ 工具：维护最大与次大，用来在不可逆合并里「拿掉某一个儿子」
// 重复的最大值必须靠 c1 计数，不能直接退回 m2
struct Top2 {
    ll m1 = -(1ll << 60), m2 = -(1ll << 60);
    int c1 = 0;
    void clear() { m1 = m2 = -(1ll << 60), c1 = 0; }
    void add(ll x) {
        if (x > m1) m2 = m1, m1 = x, c1 = 1;
        else if (x == m1) c1++;
        else if (x > m2) m2 = x;
    }
    ll best() const { return m1; }
    ll best(ll x) const { return (x == m1 && c1 == 1) ? m2 : m1; }  // 去掉一个 x 之后
};
