#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    using ll = long long;

    Node(ll l, ll r) : ls(0), rs(0), l(l), r(r), data(dataZero()), lazy(lazyZero()) {}

    [[nodiscard]] ll dataZero() { return 0; }
    [[nodiscard]] ll lazyZero() { return 0; }
    Node &operator+=(ll x) { return data += x * length(), lazy += x, *this; }
    Node &operator=(ll x) { return data = x, *this; }
    Node &update(const Node &p, const Node &q) { return update(p.data + q.data); }
    Node &update(ll x, ll y = 0) { return data = x, lazy = y, *this; }

    [[nodiscard]] ll L() { return l; }
    [[nodiscard]] ll R() { return r; }
    [[nodiscard]] bool isLeave() { return l == r; }
    [[nodiscard]] bool subOf(int L, int R) { return l >= L && r <= R; }
    [[nodiscard]] bool outOf(int L, int R) { return l > R || L > r; }
    [[nodiscard]] ll mid() const { return l + ((r - l) >> 1); }
    [[nodiscard]] ll length() const { return r - l + 1; }
    int ls, rs;
  private:
    ll l, r;
    ll data, lazy;
};

// template<typename Node = Node>
class SegTree {
  public:
    using ll = long long;
    using Order = vector<int>;

    SegTree(int n, int pos = 0) : a(1, Node(pos, pos + n - 1)) {}
    template<typename T> SegTree(const vector<T> &input, int pos) : SegTree(input.size(), pos) { build(input, pos); }

    template<typename T> 
    void build(const vector<T> &input, int pos) {
        Order order = allOrder(pos, pos + input.size() - 1);
        for (int cur : order) {
            if (a[cur].isLeave()) a[cur] = input[a[cur].L() - pos];
        }
    }

  private:
    Order allOrder(int l, int r) {
        Order order;
        if (!a[ROOT].outOf(l, r)) order.push_back(ROOT);
        for (int i = 0; i < (int) order.size(); i++) {
            int cur = order[i];
            if (a[cur].isLeave()) continue;
            if (int x = ls(cur); !a[x].outOf(l, r)) order.push_back(x);
            if (int x = rs(cur); !a[x].outOf(l, r)) order.push_back(x);
        }
        return Reverse(order);
    } 

    template<typename T> 
    static vector<T> &Reverse(vector<T> &data) { return reverse(data.begin(), data.end()), data; }

    int ls(int k) { return a[k].ls ? a[k].ls : a[k].ls = newNode(a[k].L(), a[k].mid()); }
    int rs(int k) { return a[k].rs ? a[k].rs : a[k].rs = newNode(a[k].mid() + 1, a[k].R()); }
    [[nodiscard]] int newNode(ll l, ll r) { return a.push_back(Node(l, r)), a.size() - 1; }

    vector<Node> a;
    static constexpr int ROOT = 0;
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto &i : a) cin >> i;
    SegTree s(a, 1);
    // while (q--) {
    //     long long op, l, r, x;
    //     cin >> op >> l >> r;
    //     if (op == 1) {
    //         cin >> x; 
    //         s.add(l, r, x);
    //         // for (int i = l; i <= r; i++) s.add(i, x);
    //         // for (int i = l; i <= r; i++) s.set(i, s.query(i));
    //     }
    //     else {
    //         cout << s.query(l, r) << "\n";
    //         // long long ans = 0; 
    //         // for (int i = l; i <= r; i++) ans += s.query(i); 
    //         // cout << ans << "\n";
    //     }
    // }
}