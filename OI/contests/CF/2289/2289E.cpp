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


namespace Vas {
#include <cassert>

using ll = long long;
const ll INF = 1ll << 60;
using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using pii = pair<int, int>;

struct Operation { 
    ll operator()(ll x, ll y) const { return f(x, y); } 
    ll operator*() const { return e; } 
    ll (*f)(ll, ll);
    ll e;
    template<typename F> Operation(F f, ll e = 0) : f(f), e(e) {}
};
static const Operation ADD = Operation([] (ll x, ll y) { return x + y; });
static const Operation MULTIPLE = Operation([] (ll x, ll y) { return x * y; }, 1);
static const Operation MINIMUM = Operation([] (ll x, ll y) { return min(x, y); }, INF);
static const Operation MAXIMUM = Operation([] (ll x, ll y) { return max(x, y); }, -INF);
static const Operation FORMER = Operation([] (ll x, ll) { return x; });
static const Operation LATTER = Operation([] (ll, ll y) { return y; });
    
class SegTree {
#define mid ((l + r) >> 1)
#define Ls ls[p], l, mid
#define Rs rs[p], mid + 1, r
  public:

    SegTree(
        int n = 0, int reserveSize = 0, 
        const Operation &CALCULATE = FORMER, 
        const Operation &UPDATE = MAXIMUM,
        const Operation &MERGE = MAXIMUM
    ) : n(n), CALCULATE(CALCULATE), UPDATE(UPDATE), MERGE(MERGE) {
        ls.reserve(reserveSize);
        rs.reserve(reserveSize);
        pos.reserve(reserveSize);
        data.reserve(reserveSize);
    }

    void resize(int N) { n = N; }
    void clear(int N) { resize(N), ls.clear(), rs.clear(), data.clear(), pos.clear(), cache.clear(); }

    int &modify(int &p, int POS, ll x) { return p = modify(p, 1, n, POS, x); }
    int &add(int &p, int POS, ll x) { return p = add(p, 1, n, POS, x); }
    int modify(int POS, ll x) { return modify(0, 1, n, POS, x); }
    int add(int POS, ll x) { return add(*new int(), 1, n, POS, x); }
    ll at(int p) const { return p ? data[p] : UPDATE.e;}
    ll operator[](int id) const { return at(id); }

    int merge(int p, int q) {
        if (!p || !q) return p | q;
        ls[p] = merge(ls[p], ls[q]);
        rs[p] = merge(rs[p], rs[q]);
        if (pos[p]) data[p] = MERGE(data[p], data[q]);
        else data[p] = UPDATE(calculate(p), calculate(q));
        cache.push_back(q);
        return p;
    }

    int &discard(int &p, int L, int R) { return p = discard(p, 1, n, L, R); }
    int &truncateSuf(int &p, int L) { return p = discard(p, 1, n, L, n); }
    int &truncatePre(int &p, int R) { return p = discard(p, 1, n, 1, R); }
    int &insert(int &p, int x) { return modify(p, x, 1);}

  private:
    int newNode() {
        if (!cache.empty()) {
            int p = cache.back();
            cache.pop_back();
            ls[p] = rs[p] = pos[p] = 0;
            data[p] = UPDATE.e;
            return p;
        }
        ls.push_back(0), rs.push_back(0), data.push_back(UPDATE.e);
        pos.push_back(0);
        if (data.size() <= 1) newNode();
        return data.size() - 1;
    }
    
    int modify(int p, int l, int r, int POS, ll x) {
        assert(!p || p < (int) data.size());
        if (!p) p = newNode();
        if (l == r) return data[p] = x, pos[p] = POS, p;
        POS <= mid ? ls[p] = modify(Ls, POS, x) : rs[p] = modify(Rs, POS, x);
        return update(p);
    }
    
    int add(int p, int l, int r, int POS, ll x) {
        assert(!p || p < (int) data.size());
        if (!p) p = newNode();
        if (l == r) return data[p] += x, pos[p] = POS, p;
        POS <= mid ? ls[p] = add(Ls, POS, x) : rs[p] = add(Rs, POS, x);
        return update(p);
    }

    int discard(int p, int l, int r, int L, int R) {
        if (!p || l > R || L > r) return p;
        if (l >= L && r <= R) return discard(p), 0;
        ls[p] = discard(Ls, L, R);
        rs[p] = discard(Rs, L, R);
        return update(p);
    }

    void discard(int p) {
        vi o(1, p);
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            if (!u) continue;
            o.push_back(ls[u]);
            o.push_back(rs[u]);
            cache.push_back(u);
        }
    }

    ll update(int p) { 
        if (!ls[p] && !rs[p]) return cache.push_back(p), 0;
        return data[p] = UPDATE(calculate(ls[p]), calculate(rs[p])), p; 
    }
    ll calculate(int p) const { return pos[p] ? CALCULATE(pos[p], data[p]) : data[p]; }

    int n;
    vi ls, rs, pos;
    vll data;
    const Operation CALCULATE, UPDATE, MERGE;
    vi cache;
#undef Ls
#undef Rs
#undef mid
};
}

Vas::SegTree t(0, 4e6);

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
            t.truncateSuf(rt[rs], mx[ls] + k);
            rt[u] = t.merge(rt[ls], rt[rs]);
            mx[u] = t[rt[u]];
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
