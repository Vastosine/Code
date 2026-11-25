#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

namespace Vas {

using ll = long long;
const ll INF = 1ll << 60;
using vll = vector<ll>;
using vi = vector<int>;

struct Operation { 
    inline ll operator()(ll x, ll y) const { return f(x, y); }
    inline ll operator*() const { return e; } 
    ll (*f)(ll, ll);
    ll e;
    template<typename F> Operation(F &&f, ll e = 0) : f(f), e(e) {}
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
#define This p, l, r
  public:
    SegTree(
        int n, int reserveSize = 0, 
        const Operation &CALCULATE = LATTER, 
        const Operation &UPDATE = ADD
    ) : n(n), ls(1), rs(1), data(1), CALCULATE(CALCULATE), UPDATE(UPDATE) { reserve(reserveSize); }

    void reserve(int reserveSize) {
        ls.reserve(reserveSize);
        rs.reserve(reserveSize);
        data.reserve(reserveSize);
    }

    template<typename T>
    int &build(int &p, const vector<T> &input, int pos = 1) { return p = build(p, 1, n, input, pos); }

    [[nodiscard]] int modify(int p, int pos, ll x) { return modify(p, 1, n, pos, x); }

    [[nodiscard]] ll query(int p, int pos) const { return query(p, 1, n, pos); }
  private:
    template<typename T>
    [[nodiscard]] int build(int p, int l, int r, const vector<T> &input, int pos = 1) {
        if (!p) p = newNode();
        if (l == r) return data[p] = input[l - pos], p;
        ls[p] = build(Ls, input, pos);
        rs[p] = build(Rs, input, pos);
        return update(This);
    }

    [[nodiscard]] int modify(int pre, int l, int r, int pos, ll x) {
        int p = newNode();
        if (l == r) return data[p] = x, p;
        ls[p] = ls[pre], rs[p] = rs[pre];
        pos <= mid ? ls[p] = modify(Ls, pos, x) : rs[p] = modify(Rs, pos, x);
        return update(This);
    } 

    [[nodiscard]] ll query(int p, int l, int r, int pos) const {
        if (!p) return *UPDATE;
        if (l == r) return data[p];
        return pos <= mid ? query(Ls, pos) : query(Rs, pos);
    }

    int update(int p, int l, int r) {
        if (l < r) data[p] = UPDATE(calculate(Ls), calculate(Rs));
        return p;
    }

    ll calculate(int p, int l, int r) const { return l == r ? CALCULATE(l, data[p]) : data[p]; }

    int newNode() { return ls.push_back(0), rs.push_back(0), data.push_back(*UPDATE), data.size() - 1; }

    int n;
    vi ls, rs;
    vll data;
    const Operation &CALCULATE, &UPDATE;
};

}

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;

using Vas::SegTree;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    vll a(n);
    for (ll &i : a) cin >> i;
    SegTree s(n, n << 5);
    vi rt(m + 1);
    s.build(rt[0], a);
    for (int i = 1; i <= m; i++) {
        int v, op, p;
        ll x;
        cin >> v >> op >> p;
        if (op == 1) {
            cin >> x;
            rt[i] = s.modify(rt[v], p, x);
        } else {
            rt[i] = rt[v];
            cout << s.query(rt[i], p) << "\n";
        }
    }
}

// int main() {
//     ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//     int n, m;
//     cin >> n >> m;
//     vll a(n);
//     for (ll &i : a) cin >> i;
//     SegTree s(n, n << 5);
//     vi rt(m + 1);
//     for (int i = 0; i < n; i++) {
//         rt[0] = s.modify(rt[0], i + 1, a[i]);
//     }
//     for (int i = 1; i <= m; i++) {
//         int v, op, p;
//         ll x;
//         cin >> v >> op >> p;
//         if (op == 1) {
//             cin >> x;
//             rt[i] = s.modify(rt[v], p, x);
//         } else {
//             rt[i] = rt[v];
//             cout << s.query(rt[i], p) << "\n";
//         }
//     }
// }