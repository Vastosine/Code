// Problem : P4375 [USACO18OPEN] Out of Sorts G https://www.luogu.com.cn/problem/P4375
// Time    : 2026-08-31 12:20:30

#include <iostream>
#include <vector>
#include <algorithm>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
    vi a;
    SegTree(int n) {
        a.assign(n << 2, 0);
    }

    void add(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] += x, void();
        i <= mid ? add(Ls, i, x) : add(Rs, i, x);
        a[k] += x;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n), p(n), r(n);
    cin >> a;
    p = a;
    sort(p);
    for (int i = 0; i < n; i++) {
        r[i] = std::lower_bound(p.begin(), p.end(), a[i]) - p.begin();
    }
    int ans = 1;
    SegTree s(n);
    for (int i = 1; i <= n; i++) {
        s.add(1, 1, n, r[i - 1] + 1, 1);
        int x = s.query(1, 1, n, i + 1, n);
        ans = std::max(ans, x);
    }
    cout << ans;

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