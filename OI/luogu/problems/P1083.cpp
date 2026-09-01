// Problem : P1083 [NOIP 2012 提高组] 借教室 https://www.luogu.com.cn/problem/P1083
// Time    : 2026-08-30 13:03:17

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

using std::min;
const static int INF = 0x7fffffff;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1 , r
#define lm (mid - l + 1)
#define rm (r - mid)
#define nm (r - l + 1)
    vi a, b;
    int n;
    SegTree(int n) : n(n), b(n << 2), a(n << 2, INF) {}

    SegTree(const vi &data) : n(data.size() - 1) {
        a.assign(n << 2, INF);
        b.assign(n << 2, 0);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l], void();
        build(Ls, data);
        build(Rs, data);
        a[k] = min(a[ls], a[rs]);
    }

    bool dim(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return true;
        if (l >= L && r <= R) return b[k] += x, (a[k] -= x) >= 0;
        a[ls] -= b[k];
        a[rs] -= b[k];
        b[ls] += b[k];
        b[rs] += b[k];
        b[k] = 0;
        dim(Ls, L, R, x);
        dim(Rs, L, R, x);
        return (a[k] = min(a[ls], a[rs])) >= 0;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    SegTree s(a);
    for (int i = 1; i <= m; i++) {
        int d, l, r;
        cin >> d >> l >> r;
        if (!s.dim(1, 1, n, l, r, d)) {
            cout << "-1\n" << i;
            return;
        }
    }
    cout << 0;
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