// Problem : P3373 【模板】线段树 2 https://www.luogu.com.cn/problem/P3373
// Time    : 2026-09-16 16:33:02

#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

struct Node {
#define ln ((size + 1) >> 1)
#define rn (size >> 1)
#define update data = ls->data + rs->data
#define outOf (l >= size || r <= 0)
#define of (l <= 0 && r >= size)
    const int M;
    int data, size, mul, ext;
    Node *ls, *rs;
    Node(int M) : M(M), data(0), size(0), mul(1), ext(0), ls(nullptr), rs(nullptr) {}
    Node(const int *begin, const int *end, int M) : Node(M) { build(begin, end); }

    void pushdown() {
        ls->data = (ls->data * mul + ext * ln) % M;
        rs->data = (rs->data * mul + ext * rn) % M;
        ls->mul = ls->mul * mul % M;
        rs->mul = rs->mul * mul % M;
        ls->ext = (ls->ext * mul + ext) % M;
        rs->ext = (rs->ext * mul + ext) % M;
        mul = 1;
        ext = 0;
    }

    void build(const int *begin, const int *end) {
        size = end - begin;
        if (size == 1) {
            data = *begin % M;
        } else {
            ls = new Node(begin, begin + ln, M);
            rs = new Node(begin + ln, end, M);
            update;
        }
    }

    void add(int l, int r, int x) {
        if (outOf) return;
        if (of) return (data += x * size) %= M, (ext += x) %= M, void();
        pushdown();
        ls->add(l, r, x);
        rs->add(l - ln, r - ln, x);
        update;
    }

    void mult(int l, int r, int x) {
        if (outOf) return;
        if (of) return data = data * x % M, ext = ext * x % M, mul = mul * x % M, void();
        pushdown();
        ls->mult(l, r, x);
        rs->mult(l - ln, r - ln, x);
        update;
    }

    int query(int l, int r) {
        if (outOf) return 0;
        if (of) return data;
        pushdown();
        return (ls->query(l, r) + rs->query(l - ln, r - ln)) % M;
    }
};

void solve() {
    int n, m, M;
    cin >> n >> m >> M;
    vi a(n);
    cin >> a;
    Node rt(a.begin().base(), a.end().base(), M);
    while (m--) {
        int op, l, r, x;
        cin >> op >> l >> r;
        l--;
        if (op == 3) cout << rt.query(l, r) << "\n";
        else {
            cin >> x;
            if (op == 1) rt.mult(l, r, x);
            else rt.add(l, r, x);
        }
    }
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}