// Problem : E. Danil and a Part-time Job https://codeforces.com/problemset/problem/877/E
// Time    : 2026-11-09 20:06:57
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define num (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define pushdown if (b[k]) a[ls] = lm - a[ls], a[rs] = rm - a[rs], b[ls] ^= 1, b[rs] ^= 1, b[k] = 0
#define update a[k] = a[ls] + a[rs]
    vi a, b;
    int n;
    SegTree(const vi &data) : n(data.size() - 1) {
        assign(n << 2, a, b);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l], void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void operate(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return ;
        if (l >= L && r <= R) return a[k] = num - a[k], b[k] ^= 1, void();
        pushdown;
        operate(Ls, L, R);
        operate(Rs, L, R);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

// SegTree: calculate sum. operation: 0 or 1 stand for operations % 2.
//          when operated for full operation node, sum = (r - l + 1) - sum
// when pow/get u, equals to operate/query SegTree's [dfn[u], dfn[u] + size[u] - 1], size is the subtree size
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<vi> son;
    vi fa, dfn, a, siz(n + 1, 1), ini;
    assign(n + 1, fa, dfn, a, son, ini);
    for (int i = 2; i <= n; i++) cin >> fa[i], son[fa[i]].push_back(i);
    for (int i = 1; i <= n; i++) cin >> ini[i];
    for (int i = n; i; i--) siz[fa[i]] += siz[i];
    vi st(1, 1);
    int cnt = 0;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        dfn[u] = ++cnt;
        a[dfn[u]] = ini[u];
        for (int v : son[u]) st.push_back(v);
    }
    SegTree s(a);
    int q;
    cin >> q;
    while (q--) {
        string op;
        int u;
        cin >> op >> u;
        if (op == "get") cout << s.query(1, 1, n, dfn[u], dfn[u] + siz[u] - 1) << "\n";
        else s.operate(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
