#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto &i : a) cin >> i;
    SegTree s(a, 1);
    while (q--) {
        long long op, l, r, x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x; 
            s.add(l, r, x);
            // for (int i = l; i <= r; i++) s.add(i, x);
            // for (int i = l; i <= r; i++) s.set(i, s.query(i));
        }
        else {
            cout << s.query(l, r) << "\n";
            // long long ans = 0; 
            // for (int i = l; i <= r; i++) ans += s.query(i); 
            // cout << ans << "\n";
        }
    }
}