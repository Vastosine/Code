// Problem : C. Madamant's Skating Dynasty https://codeforces.com/contest/2264/problem/C
// Time    : 2026-09-21 10:28:34

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

const int M = 998244353;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] * a[rs] % M
    vi a;
    int n;
    SegTree(int n) : n(n) {
        a.assign(n << 2, 1);
        build(1, 1,n);
    }

    void build(int k, int l, int r) {
        if (l == r) return a[k] = l, void();
        build(Ls);
        build(Rs);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 1;
        if (l >= L && r <= R) return a[k];
        return query(Ls, L, R) * query(Rs, L, R) % M;
    }

    int query(int x) {
        return query(1, 1, n, 1, x - 1) * query(1, 1, n, x + 1, n) % M;
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    if (n == 1) return cout << "0\n", void();
    SegTree s(n - 1);
    sort(a, [] (int x, int y) { return x > y; });
    int ans = 0, sum = 0;
    for (int i = 1; i < n; i++) {
        sum += a[i - 1];
        (ans += (sum - a[i] * i) % M * s.query(i)) %= M;
    }
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}