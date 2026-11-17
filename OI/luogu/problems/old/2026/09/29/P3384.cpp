// Problem : P3384 【模板】重链剖分 / 树链剖分 https://www.luogu.com.cn/problem/P3384
// Time    : 2026-09-29 21:06:51
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

int M;
vi dfn;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = (a[ls] + a[rs]) % M
#define pushdown (a[ls] += b[k] * (mid - l + 1)) %= M, (a[rs] += b[k] * (r - mid)) %= M, (b[ls] += b[k]) %= M, (b[rs] += b[k]) %= M, b[k] = 0
    vi a, b;
    int n;
    SegTree() = default;
    SegTree(const vi &data) {
        n = data.size() - 1;
        assign(n << 2, a, b);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l] % M, void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) return (a[k] += x * (r - l + 1)) %= M, (b[k] += x) %= M, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return (query(Ls, L, R) + query(Rs, L, R)) % M;
    }

    void add(int L, int R, int x) { add(1, 1, n, L, R, x); }
    int query(int L, int R) { return std::max(0ll, query(1, 1, n, L, R)); }
} s;

vi a, fa, size, son, top, data, dep, bottom;
int n, m, R;
vector<vi> e;
int dfs_cnt;

void addE(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}

void dfs1(int u, int f) {
    fa[u] = f;
    size[u] = 1;
    son[u] = 0;
    dep[u] = dep[f] + 1;
    for (int v : e[u]) {
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (!son[u] || size[son[u]] < size[v]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++dfs_cnt;
    if (son[u]) dfs2(son[u], t), bottom[u] = bottom[son[u]];
    else bottom[u] = u;
    for (int v : e[u]) {
        if (fa[u] != v && son[u] != v) dfs2(v, v);
    }
}

using std::swap;

void add(int u, int v, int x) {
    while (top[u] != top[v]) {
        int &p = dep[top[u]] > dep[top[v]] ? u : v;
        s.add(dfn[top[p]], dfn[p], x);
        p = fa[top[p]];
    }
    if (dep[v] < dep[u]) swap(u, v);
    s.add(dfn[u], dfn[v], x);
}

int query(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        int &p = dep[top[u]] > dep[top[v]] ? u : v;
        (ans += s.query(dfn[top[p]], dfn[p])) %= M;
        p = fa[top[p]];
    }
    if (dep[v] < dep[u]) swap(u, v);
    return (ans + s.query(dfn[u], dfn[v])) % M;
}

void add(int u, int x) {
    s.add(dfn[u], dfn[u] + size[u] - 1, x);
}

int query(int u) {
    return s.query(dfn[u], dfn[u] + size[u] - 1);
}

auto solve() {
    cin >> n >> m >> R >> M;
    assign(n + 1, a, e, fa, dfn, size, son, top, data, dep, bottom);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addE(u, v);
    }
    dfs1(R, 0);
    dfs2(R, R);
    for (int i = 1; i <= n; i++) data[dfn[i]] = a[i];
    s = data;
    while (m--) {
        int op, u, v, x;
        cin >> op >> u;
        if (op == 4) cout << query(u) << "\n";
        else {
            cin >> v;
            if (op == 3) add(u, v);
            else if (op == 2) cout << query(u, v) << "\n";
            else cin >> x, add(u, v, x);
        }
    }
    return 0;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}