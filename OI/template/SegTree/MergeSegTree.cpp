// 线段树合并（值域 [1, n] 的动态开点权值线段树）
//
// 用途：n 棵各自很小的树自底向上合并成一棵，每棵树代表一个集合。
//       典型题：树上每个点一个集合、按值域统计、DSU on tree 的替代。
//
// 支持的操作：
//   insert(p, x)        往根为 p 的集合里插入 x，返回新的根
//   merge(a, b)         把 b 合并进 a，返回合并后的根；**b 之后不可再用**
//   truncate(&p, T)     删掉所有 > T 的元素（这题 2289E 需要它）
//   pred(p, T)          最大的 <= T 的元素，空则返回 0
//   maximum(p)          整棵集合的最大值
//
// 复杂度：
//   插入 O(log n)
//   merge 的总代价 O(总节点数)，**不是** 每次 O(log²) —— 见下方说明
//   截断 / 前驱 各 O(log n)
//
// 为什么 merge 是摊还 O(总节点数)：
//   递归只在「a 和 b 的这个儿子都非空」时发生。一旦递归进去，b 的这个节点就被
//   永久丢弃，之后不会再被访问。所以递归总次数 <= 被丢弃的节点总数。
//
// 内存：
//   总节点数 = 总插入次数 * O(log n)。n = 2e5 时约 3.6e6，MAXNODE 开 4e6。
//   多测只在 clear() 里把 cnt 置 0 复用内存，不要每测重新 assign。
//
// 注意：
//   1. 值域必须从 1 开始 —— 用 0 当「空」的标记。
//   2. truncate 的参数是引用：它需要能把 p 本身置 0。
//   3. merge 会就地改写 a 并丢弃 b，不要在有别处引用 b 的时候调。

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class MergeSegTree {
  public:
    MergeSegTree(int n = 0, int maxNode = 0) { init(n, maxNode); }

    void init(int n_, int maxNode) {
        n = n_;
        cnt = 0;
        lc.assign(maxNode + 1, 0);
        rc.assign(maxNode + 1, 0);
        mx.assign(maxNode + 1, 0);
    }

    void clear() { cnt = 0; }  // 多测：只清计数，内存复用

    int insert(int p, int x) { return insert(p, 1, n, x); }

    int merge(int a, int b) {
        if (!a || !b) return a | b;
        lc[a] = merge(lc[a], lc[b]);
        rc[a] = merge(rc[a], rc[b]);
        mx[a] = max(mx[a], mx[b]);
        return a;
    }

    void truncate(int &p, int T) { truncate(p, 1, n, T); }

    int pred(int p, int T) const { return pred(p, 1, n, T); }

    int maximum(int p) const { return p ? mx[p] : 0; }

    int nodeCount() const { return cnt; }

  private:
    int newNode() {
        ++cnt;
        lc[cnt] = rc[cnt] = mx[cnt] = 0;
        return cnt;
    }

    int insert(int p, int l, int r, int x) {
        if (!p) p = newNode();
        if (l == r) return mx[p] = x, p;
        int m = (l + r) >> 1;
        if (x <= m) lc[p] = insert(lc[p], l, m, x);
        else rc[p] = insert(rc[p], m + 1, r, x);
        return mx[p] = max(mx[lc[p]], mx[rc[p]]), p;
    }

    void truncate(int &p, int l, int r, int T) {
        if (!p || r <= T) return;
        if (l > T) return p = 0, void();
        int m = (l + r) >> 1;
        truncate(lc[p], l, m, T);
        truncate(rc[p], m + 1, r, T);
        mx[p] = max(mx[lc[p]], mx[rc[p]]);
        if (!mx[p]) p = 0;  // 整棵空了就断开引用（不回收节点）
    }

    int pred(int p, int l, int r, int T) const {
        if (!p || l > T) return 0;
        if (r <= T) return mx[p];
        int m = (l + r) >> 1;
        int res = pred(rc[p], m + 1, r, T);
        return res ? res : pred(lc[p], l, m, T);
    }

    int n, cnt;
    vector<int> lc, rc, mx;
};

// ---- 下方是自检，抄进题解时整段删掉 ----
static void selfCheck() {
    srand(20261123);
    int bad = 0;
    for (int round = 0; round < 400; round++) {
        const int N = 1 + rand() % 8;
        const int K = 1 + rand() % 4;
        MergeSegTree st(N, 2000);
        vector<int> root(K, 0);
        vector<set<int>> ref(K);
        for (int step = 0; step < 60; step++) {
            int op = rand() % 4;
            int t = rand() % K;
            if (op == 0) {
                int x = 1 + rand() % N;
                root[t] = st.insert(root[t], x);
                ref[t].insert(x);
            } else if (op == 1) {
                int T = rand() % (N + 1);
                st.truncate(root[t], T);
                vector<int> del;
                for (int v : ref[t]) if (v > T) del.push_back(v);
                for (int v : del) ref[t].erase(v);
            } else if (op == 2) {
                int T = rand() % (N + 1);
                int got = st.pred(root[t], T);
                int want = 0;
                for (int v : ref[t]) if (v <= T) want = max(want, v);
                if (got != want) {
                    bad++;
                    if (bad <= 3) fprintf(stderr, "pred bad: N=%d T=%d got=%d want=%d\n", N, T, got, want);
                }
            } else {
                int s = rand() % K;
                if (s == t) continue;
                root[t] = st.merge(root[t], root[s]);
                for (int v : ref[s]) ref[t].insert(v);
                ref[s].clear();
                root[s] = 0;
            }
            int got = st.maximum(root[t]);
            int want = ref[t].empty() ? 0 : *ref[t].rbegin();
            if (got != want) {
                bad++;
                if (bad <= 3) fprintf(stderr, "max bad: got=%d want=%d\n", got, want);
            }
        }
    }
    printf("selfCheck bad = %d\n", bad);
}

int main() { selfCheck(); }
