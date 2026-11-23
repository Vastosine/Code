// Problem : E. The Problem from Silach https://codeforces.com/contest/2289/problem/E
// Time    : 2026-11-22 17:05:15
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

class MergeSegTree {
  public:
    // reserveNodes 不传也行：靠 push_back 动态增长，永远不会越界。
    // 传了只是免掉重分配（以及免掉「引用在扩容后悬垂」这类雷），不是上界。
    MergeSegTree(int n = 0, int reserveNodes = 0) { init(n, reserveNodes); }

    void init(int n_, int reserveNodes = 0) {
        n = n_;
        lc.assign(1, 0);
        rc.assign(1, 0);
        mx.assign(1, 0);  // 0 号是空节点
        if (reserveNodes > 0) {
            lc.reserve(reserveNodes + 1);
            rc.reserve(reserveNodes + 1);
            mx.reserve(reserveNodes + 1);
        }
    }

    // 多测：resize 回 1 号，容量保留，内存复用。不要 assign —— 语义会让人以为清空了容量
    void clear(int N) {
        n = N;
        clear();
    }

    void clear() {
        lc.resize(1);
        rc.resize(1);
        mx.resize(1);
    }

    int nodeCount() const { return (int) lc.size() - 1; }

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

  private:
    int newNode() {
        lc.push_back(0);
        rc.push_back(0);
        mx.push_back(0);
        return (int) lc.size() - 1;
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

    int n;
    vector<int> lc, rc, mx;
};

MergeSegTree t(0, 4e6);

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    int N = n * 2;
    vector<vi> son;
    vi mx, dep;
    assign(N, son, mx, dep);
    const int D = __lg(n) + 1;
    vector<vi> fa(D + 1, vi(N)), mn(D + 1, vi(N));
    int s = n * 2 - 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        son[i + n] = {u, v};
        fa[0][u] = fa[0][v] = i + n;
    }
    fa[0][s] = s;
    vi o(1, s);
    dep[s] = 1;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : son[u]) {
            dep[v] = dep[u] + 1;
            o.push_back(v);
        }
    }
    t.clear(n);
    vi rt(N);
    for (int i = (int) o.size() - 1; ~i; i--) {
        int u = o[i];
        if (u <= n) mx[u] = u, rt[u] = t.insert(rt[u], u);
        else {
            int ls = son[u][0], rs = son[u][1];
            if (mx[ls] > mx[rs]) swap(ls, rs);
            t.truncate(rt[rs], mx[ls] + k - 1);
            rt[u] = t.merge(rt[ls], rt[rs]);
            mx[u] = t.maximum(rt[u]);
            // mx[u] = min({mx[ls] + k - 1, mx[rs] + k - 1, max(mx[ls], mx[rs])});
        }
    }
    // cout << mx << "\n";
    for (int u = 1; u < N; u++) mn[0][u] = min(mx[u], mx[fa[0][u]]);
    for (int d = 0; d < D; d++) {
        for (int u = 1; u < N; u++) {
            fa[d + 1][u] = fa[d][fa[d][u]];
            mn[d + 1][u] = min(mn[d][u], mn[d][fa[d][u]]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int u = i;
        for (int d = D; ~d; d--) {
            if (mn[d][u] >= i) u = fa[d][u]; 
        }
        cout << dep[i] - dep[u] + (u != N - 1) << " ";
    }
    cout << "\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
