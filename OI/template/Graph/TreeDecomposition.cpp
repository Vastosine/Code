// siz[fa[u]] += siz[u], (bfs) / siz[u] = 1 + sum{ siz[v], fa[v] = u }, dfs
// son[u] = v | siz[v] is max within fa[v] = u
// when go son[u], top remains, otherwise top is the vertice currently
// dfn[u] = ++cnt;
// LCA : ans = vertice whose depth is smaller when top[u] == top[v];
//       if (top[u] != top[v]) the depth of top deeper jump to its fa[top]
// path sum/modify: the same to LCA, but calculate/modify when jump to top or jump to depth-lower
// subtree sum/modify: calculate/modify [dfn[u], dfn[u] + siz[u])

#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

struct SegTree {
#define ls (k << 1) 
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define pushdown a[ls] += b[k] * (mid - l + 1), a[rs] += b[k] * (r - mid), b[ls] += b[k], b[rs] += b[k], b[k] = 0
#define update a[k] = a[ls] + a[rs]
    vll a, b;
    int n;
    SegTree(int n = 0) : n(n), a(n << 2), b(n << 2) {}

    SegTree(const vll &data) : SegTree(data.size() - 1) { build(1, 1, n, data); }

    void build(int k, int l, int r, const vll &data) {
        if (l == r) return a[k] = data[l], void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void add(int k, int l, int r, int L, int R, ll x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) return a[k] += x * (r - l + 1), b[k] += x, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }

    void add(int L, int R, ll x) { add(1, 1, n, L, R, x); }
    ll query(int L, int R) { return query(1, 1, n, L, R); }
};

// e and val(initial value of vertice) are given by main()
vector<vi> e;
vll val;
vi dep, siz, son, dfn, fa, top;
SegTree s;
int n;

void init() {
    dep.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    son.assign(n + 1, 0);
    fa.assign(n + 1, 0);
    siz.assign(n + 1, 0);
    top.assign(n + 1, 0);
    vi o(1, 1);
    fa[1] = 1, dep[1] = 1, top[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!fa[v]) fa[v] = u, o.push_back(v), dep[v] = dep[u] + 1;
        }
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        siz[u] = 1;
        for (int v : e[u]) {
            if (fa[v] == u) {
                siz[u] += siz[v];
                if (!son[u] || siz[v] > siz[son[u]]) son[u] = v;
            }
        }
    }
    vi st(1, 1);
    vll data(n + 1);
    int cnt = 0;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        dfn[u] = ++cnt;
        data[dfn[u]] = val[u];
        for (int v : e[u]) {
            if (fa[v] == u && v != son[u]) {
                st.push_back(v);
                top[v] = v;
            }
        }
        if (son[u]) st.push_back(son[u]), top[son[u]] = top[u];
    }
    s = data;
}

int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void add(int u, int v, ll x) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        s.add(dfn[top[u]], dfn[u], x);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    s.add(dfn[v], dfn[u], x);
}

ll query(int u, int v) {
    ll ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += s.query(dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    return ans + s.query(dfn[v], dfn[u]);
}

void add(int u, ll x) {
    s.add(dfn[u], dfn[u] + siz[u] - 1, x);
}

ll query(int u) {
    return s.query(dfn[u], dfn[u] + siz[u] - 1);
}