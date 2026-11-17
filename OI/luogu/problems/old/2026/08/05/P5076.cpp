// Problem : P5076 【深基16.例7】普通二叉树（简化版） https://www.luogu.com.cn/problem/P5076
// Time    : 2026-08-05 20:14:25

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

class BinaryTree {
#define ls (a[p].left)
#define rs (a[p].right)
#define ln (a[ls].size)
    struct Node {
        int left, right, size, value;
        Node() : left(0), right(0), size(0), value(0) {}
        Node(int x) : left(0), right(0), size(1), value(x) {}
        operator int() const { return value; }
        int operator*() const { return value; }
    };

  public:

    BinaryTree(int n = 1) : a(1) {
        a.reserve(n + 1);
    }

    void insert(int x, int p = ROOT) {
        if (a.size() == 1) return add(x), void();
        a[p].size++;
        if (x == a[p]) return;
        if (x < a[p]) {
            if (ls) return insert(x, ls);
            ls = add(x);
        } else {
            if (rs) return insert(x, rs);
            rs = add(x);
        }
    }

    int get(int n, int p = ROOT) const {
        if (n == ln) return a[p];
        if (n < ln) return get(n, ls);
        return get(n - ln - 1, rs);
    }

    int rank(int x, int p = ROOT) const {
        if (!p) return 0;
        if (x == a[p]) return ln;
        if (x < a[p]) return rank(x, ls);
        return ln + 1 + rank(x, rs);
    }

    int pre(int x, int p = ROOT) const {
        if (!p) return -inf;
        if (x <= a[p]) return pre(x, ls);
        int ans = pre(x, rs);
        return ans == -inf ? *a[p] : ans;
    }

    int next(int x, int p = ROOT) const {
        if (!p) return inf;
        if (x >= a[p]) return next(x, rs);
        int ans = next(x, ls);
        return ans == inf ? *a[p] : ans;
    }

  private:
    int add(int x) {
        a.push_back(x);
        return a.size() - 1;
    }

    vector<Node> a;
    static const int ROOT = 1;
    static const int EMPTY = 0;
    static const int inf = 0x7fffffff;
};


void solve() {
    int n;
    cin >> n;
    BinaryTree a(n);
    while (n--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
        case 1: { cout << a.rank(x) + 1 << "\n"; break; }
        case 2: { cout << a.get(x - 1) << "\n"; break; }
        case 3: { cout << a.pre(x) << "\n"; break; }
        case 4: { cout << a.next(x) << "\n"; break; }
        case 5: { a.insert(x); break; }
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}