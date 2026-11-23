#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
struct Operation { 
    ll operator()(ll x, ll y) { return f(x, y); } 
    ll (*f)(ll, ll);
    template<typename F> Operation(F f) : f(f) {}
};
static const Operation ADD = Operation([] (ll x, ll y) { return x + y; });
static const Operation MINIMUM = Operation([] (ll x, ll y) { return min(x, y); });
static const Operation MAXIMUM = Operation([] (ll x, ll y) { return max(x, y); });
    
class SegTree {
#define mid ((l + r) >> 1)
#define Ls ls[p], l, mid
#define Rs rs[p], mid + 1, r
#define update data[p] = UPDATE(data[ls[p]], data[rs[p]])
  public:
    using ll = long long;
    using vll = vector<ll>;
    using vi = vector<int>;
    using pii = pair<int, int>;


    SegTree(int n = 0, int reserveSize = 0, const Operation &UPDATE = ADD) : n(n), UPDATE(UPDATE) {
        ls.reserve(reserveSize);
        rs.reserve(reserveSize);
        data.reserve(reserveSize);
    }

    void resize(int N) { n = N; }
    void setUpdateMode(const Operation &updateMode) { UPDATE = updateMode; }
    void clear(int N) { resize(N), ls.clear(), rs.clear(), data.clear(); }

    int &modify(int &p, int pos, ll x) { return p = modify(p, 1, n, pos, x); }
    int &add(int &p, int pos, ll x) { return p = add(p, 1, n, pos, x); }
    int modify(int pos, ll x) { return modify(0, 1, n, pos, x); }
    int add(int pos, ll x) { return add(*new int(), 1, n, pos, x); }

    ll &at(int &p, int pos) { return at(!p ? p = newNode() : p, 1, n, pos).second; }
    ll &operator[](pair<int&, int> id) { return at(id.first, id.second); }
    ll at(int &&p, int pos) { return at(p, 1, n, pos).second; }
    ll operator[](const pair<int&&, int> &id) { return at(id.first, 1, n, id.second).second; }
    ll at(int p, int pos) const { return at(p, 1, n, pos); }
    ll operator[](const pii &id) const { return at(id.first, id.second); }

  public:
    int newNode() {
        ls.push_back({}), rs.push_back({}), data.push_back({});
        if (data.size() <= 1) newNode();
        return data.size() - 1;
    }
    
    int modify(int p, int l, int r, int pos, ll x) {
        assert(!p || p < (int) data.size());
        if (!p) p = newNode();
        if (l == r) return data[p] = x, p;
        pos <= mid ? ls[p] = modify(Ls, pos, x) : rs[p] = modify(Rs, pos, x);
        return update, p;
    }
    
    int add(int p, int l, int r, int pos, ll x) {
        assert(!p || p < (int) data.size());
        if (!p) p = newNode();
        if (l == r) return data[p] += x, p;
        pos <= mid ? ls[p] = add(Ls, pos, x) : rs[p] = add(Rs, pos, x);
        return update, p;
    }

    pair<int, ll&> at(int p, int l, int r, int pos) { 
        assert(!p || p < (int) data.size());
        if (!p) p = newNode();
        if (l == r) return{ p, data[pos] };
        auto [id, val] = pos <= mid ? at(Ls, pos) : at(Rs, pos);
        (pos <= mid ? ls[p] : rs[p]) = id;
        return {p, val};
    }
    ll at(int p, int l, int r, int pos) const {
        assert(p && p < (int) data.size());
        return l == r ? data[pos] : pos <= mid ? at(Ls, pos) : at(Rs, pos);
    }

    int n;
    vi ls, rs;
    vll data;
    Operation UPDATE;
#undef Ls
#undef Rs
#undef mid
#undef update
};
int main() {
    SegTree s(5);
    int rt = 0;
    s.at(1, 1);
    s[{rt, 1}] = 1;
    cout << s[{1, 2}] << "\n";
}