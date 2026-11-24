#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

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


int main() {
    Vas::SegTree s(5, 0, Vas::MULTIPLE, Vas::ADD, Vas::ADD);
    int rt = s.modify(1, 2);
    s.modify(rt, 2, 3);
    cout << s[rt] << "\n";
}