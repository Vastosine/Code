// Problem : G. Nightcrawler https://codeforces.com/contest/2254/problem/G
// Time    : 2026-09-28 16:22:05
#include <iostream>
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
using std::min;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = min(a[ls], a[rs])
#define pushdown a[ls] += b[k], a[rs] += b[k], b[ls] += b[k], b[rs] += b[k], b[k] = 0
    vi a, b;
    int n;
    SegTree() = default;
    SegTree(const vi &data) {
        n = data.size() - 1;
        assign(n << 2, a, b);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l], void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) return a[k] += x, b[k] += x, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 1e18;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return min(query(Ls, L, R), query(Rs, L, R));
    }

    void add(int L, int R, int x) { add(1, 1, n, L, R, x); }
    void add(int i, int x) { add(1, 1, n, i, i, x); }
    int query(int L, int R) { return query(1, 1, n, L, R); }
} tr;

int n, cnt;
vi a, dep, son, fa, size, top, dfn, data, lsize;
vector<vi> s;

void dfs1(int u = 1) {
    dep[u] = dep[fa[u]] + 1;
    size[u] = 1;
    son[u] = 0;
    lsize[u] = s[u].empty();
    for (int v : s[u]) {
        dfs1(v);
        size[u] += size[v];
        if (!son[u] || size[son[u]] < size[v]) son[u] = v;
        lsize[u] += lsize[v];
    }
}

void dfs2(int u = 1, int t = 1) {
    dfn[u] = ++cnt;
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (int v : s[u]) {
        if (v != son[u]) dfs2(v, v);
    }
}   

void add(int u, int v, int x) {
    while (top[u] != top[v]) {
        int &p = dep[top[u]] > dep[top[v]] ? u : v;
        tr.add(dfn[top[p]], dfn[p], x);
        p = fa[top[p]];
    }
    if (dep[v] < dep[u]) std::swap(u, v);
    tr.add(dfn[u], dfn[v], x);
}

int query(int u, int v) {
    int ans = 1e18;
    while (top[u] != top[v]) {
        int &p = dep[top[u]] > dep[top[v]] ? u : v;
        ans = min(ans, tr.query(dfn[top[p]], dfn[p]));
        p = fa[top[p]];
    }
    if (dep[v] < dep[u]) std::swap(u, v);
    return min(ans, tr.query(dfn[u], dfn[v]));
}

auto solve() {
    cnt = 0;
    cin >> n;
    assign(n + 1, lsize, a, s, dep, son, fa, size, top, dfn, data);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) cin >> fa[i], s[fa[i]].push_back(i);
    dfs1();
    dfs2();
    for (int i = 1; i <= n; i++) data[dfn[i]] = lsize[i];
    tr = data;
    vector<int> srt;
    for (int i = 1; i <= n; i++) srt.push_back(i);
    sort(srt, [] (int x, int y) { return a[x] > a[y]; });
    int x = lsize[1];
    vi ans(x - 1, -1), vis(n + 1);
    int y = 0;
    for (int i : srt) {
        if (query(1, i) > 0) 
            add(1, i, -1), y += a[i], vis[i] = 1;
    }
    ans.push_back(y);
    for (int i : srt) {
        if (!vis[i]) ans.push_back(ans.back() + a[i]);
    }
    return ans;
    // return 0;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}