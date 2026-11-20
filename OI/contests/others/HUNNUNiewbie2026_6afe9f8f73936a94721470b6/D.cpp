// Problem : $name$ $url$
// Time    : $date$ $time$
#include <algorithm>
#include <iostream>
#include <set>
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

class SegTree {
  public:
    using ll = long long;
    using vll = vector<ll>;
    using Order = vector<SegTree*>;

    SegTree(ll l, ll r) : L(l), R(r), LS(0), RS(0), data(getZero()), lazy(lazyZero()) {}
    template<typename T> SegTree(const vector<T> &input, ll start = 0) : SegTree(start, start + (ll) input.size() - 1) { fill(input, start); }

    // Only need to modify these function
    void update() { if (!isLeave()) data = ls()->data + rs()->data, lazy = lazyZero(); }
    SegTree &operator+=(ll x) { data += x * size(); if (!isLeave()) lazy += x; return *this; };
    void pushdown() { *ls() += lazy, *rs() += lazy, lazy = lazyZero(); }
    bool needPushdown() { return lazy; }
    ll getZero() { return 0; }
    ll lazyZero() { return 0; }

    template<typename T> 
    void fill(const vector<T> &input, int start = 0) {
        Order order = allOrder(start, start + (int) input.size() - 1);
        for (SegTree *cur : order) {
            if (cur->isLeave()) cur->data = input[cur->L - start];
            else cur->update();
        }
    }

    void set(ll id, ll x) {
        Order order = getOrder(id);
        order.front()->data = x;
        for (SegTree *cur : order) cur->update();
    }
    
    void add(ll id, ll x) {
        Order order = getOrder(id);
        order.front()->data += x;
        for (SegTree *cur : order) cur->update();
    }
    
    void add(ll l, ll r, ll x) {
        Order order = getOrder(l, r);
        for (SegTree *cur : order) {
            if (cur->in(l, r)) *cur += x;
            else cur->update();
        }
    }

    ll query(ll id) { return getOrder(id).front()->data; }
    
    ll query(ll l, ll r) {
        ll ans = getZero();
        Order order = getOrder(l, r);
        for (SegTree *cur : order) {
            if (cur->in(l, r)) ans += cur->data;
        }
        return ans;
    }

    template<typename T>
    static void Reverse(vector<T> &a) { reverse(a.begin(), a.end()); }

    ~SegTree() { delete LS, delete RS; }
  private:
    bool isLeave() { return L == R; }
    bool in(int l, int r) { return L >= l && R <= r; }
    ll size() { return R - L + 1; }
    ll mid() { return (L + R) >> 1; }
    SegTree *ls() { return LS ? LS : LS = new SegTree(L, mid()); }
    SegTree *rs() { return RS ? RS : RS = new SegTree(mid() + 1, R); }

    Order getOrder(ll id, bool rvs = true) {
        if (id < L || id > R) return {};
        Order order(1, this);
        for (int i = 0; i < (int) order.size(); i++) {
            SegTree *cur = order[i];
            if (cur->needPushdown()) cur->pushdown();
            if (cur->isLeave()) continue;
            order.push_back(id <= cur->mid() ? cur->ls() : cur->rs());
        }
        if (rvs) Reverse(order);
        return order;
    }

    Order getOrder(ll l, ll r, bool rvs = true) {
        if (l > R || L > r) return {};
        Order order(1, this);
        for (int i = 0; i < (int) order.size(); i++) {
            SegTree *cur = order[i];
            if (cur->needPushdown()) cur->pushdown(); 
            if ((cur->in(l, r)) || cur->L > r || l > cur->R) continue;
            if (l <= cur->mid()) order.push_back(cur->ls());
            if (r > cur->mid()) order.push_back(cur->rs());
        }
        if (rvs) Reverse(order);
        return order;
    }

    Order allOrder(int l, int r, bool rvs = true) {
        if (l > R || L > r) return {};
        Order order(1, this);
        for (int i = 0; i < (int) order.size(); i++) {
            SegTree *cur = order[i];
            if (cur->isLeave() || l > R || L > r) continue;
            if (l <= cur->mid()) order.push_back(cur->ls());
            if (r > cur->mid()) order.push_back(cur->rs());
        }
        if (rvs) Reverse(order);
        return order;
    }
    
    const ll L, R;
    SegTree *LS, *RS;
    ll data, lazy;
};

auto Main([[maybe_unused]] int C = 0) {
    SegTree s(0, 2e9);const ll NEG = -4e18, POS = 4e18;
multiset<ll> t{NEG, POS};
    int n;
    cin >> n;
    auto add = [&] (int x, int y, int z) {
        s.add(abs(x - y) + 1, x + y - 1, z);
    };
    int ans = 0;
    while (n--) {
        ll op, x;
        cin >> op >> x;
        if (op == 3) {
            if (s.query(x)) {
                ans++;
                cout << x << "\n";
            }
            continue;
        } if (op == 1) {
            auto it = t.lower_bound(x);
            ll r = *it, l = *prev(it);
            if (l != NEG) s.add(l, x, 1);
            if (r != POS) s.add(x, r, 1);
            if (l != NEG && r != POS) s.add(l, r, -1);
            t.insert(x);
        } else {
            auto it = t.find(x);
            ll l = *prev(it), r = *next(it);
            if (l != NEG) s.add(l, x, -1);
            if (r != POS) s.add(x, r, -1);
            if (l != NEG && r != POS) s.add(l, r, 1);
            t.erase(it);
        }
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
