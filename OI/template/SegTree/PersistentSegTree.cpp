#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

namespace Vas {

using ll = long long;
const ll INF = 1ll << 60;

struct Operation { 
    inline ll operator()(ll x, ll y) const { return f(x, y); }
    inline ll operator*() const { return e; } 
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
  public:
    SegTree(
        int l, int r, 
        const Operation &CALCULATE = LATTER, 
        const Operation &UPDATE = ADD
    ) : l(l), r(r), data(*UPDATE), LS(0), RS(0), CALCULATE(CALCULATE), UPDATE(UPDATE) {}

    SegTree(
        int n, 
        const Operation &CALCULATE = LATTER, 
        const Operation &UPDATE = ADD
    ) : SegTree(1, n, CALCULATE, UPDATE) {}

    template<typename T>
    SegTree(
        const vector<T> &lst, 
        int pos = 0,
        const Operation &CALCULATE = LATTER, 
        const Operation &UPDATE = ADD
    ) : SegTree(pos, pos + (int) lst.size() - 1, CALCULATE, UPDATE) {
        build(lst, pos);
    }

    ~SegTree() { delete LS, delete RS; }

    template<typename T>
    SegTree *build(const vector<T> &lst, int pos = 0) {
        if (l == r) return data = lst[l - pos], this;
        ls()->build(lst, pos);
        rs()->build(lst, pos);
        update();
        return this;
    }

    SegTree *modify(int pos, ll x) {
        if (pos > r || pos < l) return 0;
        SegTree *p = newNode(l, r);
        if (l == r) return p->data = x, p;
        pos <= mid() ? (p->LS = ls()->modify(pos, x), p->RS = rs()) : (p->RS = rs()->modify(pos, x), p->LS = ls());
        update();
        return p;
    }

    ll query(int pos) const {
        if (pos > r || pos < l) return *UPDATE;
        if (l == r) return data;
        if (pos <= mid()) return LS ? ls()->query(pos) : *UPDATE;
        else return RS ? rs()->query(pos) : *UPDATE;
    }

  private:
    SegTree *newNode(int _l, int _r) const { return new SegTree(_l, _r, CALCULATE, UPDATE); }
    int mid() const { return (l + r) >> 1; }
    ll update() { return l == r ? data : data = UPDATE(ls()->calculate(), rs()->calculate()); }
    ll calculate() const { return l == r ? CALCULATE(l, data) : data; }
    SegTree *&ls() { return LS ? : LS = newNode(l, mid()); }
    SegTree *ls() const { assert(LS); return LS; }
    SegTree *&rs() { return RS ? : RS = newNode(mid() + 1, r); }
    SegTree *rs() const { assert(RS); return RS; }

    int l, r;
    ll data;
    SegTree *LS, *RS;
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
    vector<SegTree*> rt(m + 1);
    rt[0] = new SegTree(a, 1);
    for (int i = 1; i <= m; i++) {
        int v, op, p;
        ll x;
        cin >> v >> op >> p;
        if (op == 1) {
            cin >> x;
            rt[i] = rt[v]->modify(p, x);
        } else {
            rt[i] = rt[v];
            cout << rt[i]->query(p) << "\n";
        }
    }
}