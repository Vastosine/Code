// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
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
void init() {}

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define pushdown a[ls] += b[k], a[rs] += b[k], b[ls] += b[k], b[rs] += b[k], b[k] = 0
#define update a[k] = min(a[ls], a[rs])
    int n;
    vll a, b;
    SegTree(const vi &data) {
        n = (int) data.size();
        a.assign(n << 2, 0);
        b.assign(n << 2, 0);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l - 1], void();
        build(Ls, data); build(Rs, data);
        update;
    }

    void add(int k, int l, int r, int L, int R, ll x) {
        if (l > R || L > r) return ;
        if (l >= L && r <= R) return a[k] += x, b[k] += x, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return INF;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return min(query(Rs, L, R), query(Ls, L, R));
    }

    void add(int l, int r, ll x) {
        add(1, 1, n, l + 1, r, x);
    }

    ll query(int l, int r) {
        return query(1, 1, n, l + 1, r);
    }
}; 

auto Main([[maybe_unused]] int C = 0) {
    int n, q;
    cin >> n >> q;
    vi a(n - 1);
    cin >> a;
    vector<pii> p(q);
    for (auto &[u, v] : p) {
        cin >> u >> v;
        if (u < v) swap(u, v);
    }
    Sort(p);
    // for (auto &[u, v] : p) {
    //     cout << u << " " << v << "\n";
    // }
    SegTree s(a);
    ll ans = 0;
    for (auto &[u, v] : p) {
        ll x = s.query(v, u);
        s.add(v, u, -x);
        ans += x;
    }
    return ans;
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
