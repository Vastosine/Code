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

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    int N = n * 2;
    vector<vi> son;
    vi mx, dep;
    assign(N, son, mx, dep);
    const int D = __lg(n) + 1;
    vector<vi> fa(N, vi(D + 1)), mn(N, vi(D + 1));
    int s = n * 2 - 1;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        son[i + n] = {u, v};
        fa[u][0] = fa[v][0] = i + n;
    }
    fa[s][0] = s;
    vi o(1, s);
    dep[s] = 1;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : son[u]) {
            dep[v] = dep[u] + 1;
            o.push_back(v);
        }
    }
    MergeSegTree t(N, N << 4);
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
    for (int u = 1; u < N; u++) mn[u][0] = min(mx[u], mx[fa[u][0]]);
    for (int d = 0; d < D; d++) {
        for (int u = 1; u < N; u++) {
            fa[u][d + 1] = fa[fa[u][d]][d];
            mn[u][d + 1] = min(mn[u][d], mn[fa[u][d]][d]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int u = i;
        for (int d = D; ~d; d--) {
            if (mn[u][d] >= i) u = fa[u][d]; 
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
