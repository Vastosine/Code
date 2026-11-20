// Problem : 捕风的异乡人 https://ac.nowcoder.com/acm/contest/142131/J
// Time    : 2026-10-18 15:43:41
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename T, typename... Args> void asv(int n, T &&v, vector<Args>&... args) { (..., args.assign(n, v)); }
template<typename F, typename T, typename... Args> T &update(F &&f, T &x, Args &&...args) { return ((x = f(x, args)), ...), x; }
template<typename F, typename T, typename... Args> T func(F &&f, const T &x, Args &&...args) { T tmp(x); return ((tmp = f(tmp, args)), ...), tmp; }

using std::max;

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
    vi a;
    SegTree(int n) : a(n << 2, -1e18) {}
    void modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x, void();
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        a[k] = max(a[ls], a[rs]);
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return -1e18;
        if (l >= L && r <= R) return a[k];
        return max(query(Ls, L, R), query(Rs, L, R));
    }
};


auto solve() {
    int n, k, u;
    cin >> n >> k >> u;
    vi a(n + 1), low(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int l = n, r = n, s = 1; r; r--) {
        while (l && u % a[l] == 0 && (u / a[l]) % s == 0) s *= a[l--];
        low[r] = l + 1;
        if (l >= r) s = 1, l = r - 1;
        else s /= a[r];
    }
    SegTree s(n);
    vi f(n + 1);
    for (int i = 1; i < k; i++) s.modify(1, 1, n, i, f[i] = -1e18);
    for (int i = k; i <= n; i++) {
        int l = low[i];
        f[i] = max(0ll, max(max(l == 1 ? 0ll : (int) -1e18, s.query(1, 1, n, l - 1, i - k)) + 1, s.query(1, 1, n, 1, i - k)));
        s.modify(1, 1, n, i, f[i]);
    }
    return f.back();
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    while (c--) cout << solve() << "\n";
    // while (c--) {
    //     vi ans = solve();
    //     if (ans.empty()) cout << "NO";
    //     else cout << "YES\n" << ans << "\n";
    // }
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}