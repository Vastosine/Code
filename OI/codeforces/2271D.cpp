// Problem : D. Target Infection https://codeforces.com/problemset/problem/2271/D
// Time    : 2026-10-20 22:09:31
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

int solve(int c) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vi> a(n, vi(2));
    cin >> a;
    // if (c == 2394) cout << n << m << k << "\n";
    // if (c == 2394) cout << a[0][0] << a[0][1] << a[1][0] << a[1][1] << "\n";
    vi b(n);
    int p = -1, q = 0;
    if (!k) return 1e17; 
    for (int l = 0, r = 0, s = 0; l < n; l++) {
        while (r < n && a[r][1] < a[l][0] + m) s += a[r][1] - a[r][0] + 1, r++;
        b[l] = r == n ? s : s + std::max(a[l][0] + m - a[r][0], 0ll);
        if (b[l] == k) return a[l][0];
        if (b[l] > k) p = l, q = r;
        s -= a[l][1] - a[l][0] + 1;
    }
    if (p < 0) return -1;
    // cout << b << "  " << p << "\n";
    int t = b[p] - k, x = a[p][0];
    if (q == n) return a[p][0] + t;
    if (!q) x = a[0][1] - m + 1, q++;
    while (q < n) {
        if (t <= a[q][0] - (x + m)) return x + t;
        t -= std::max(0ll, a[q][0] - (x + m));
        x += a[q][1] - (x + m) + 1;
        q++;
    }
    return x + t;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    for (int i = 1; i <= c; i++) cout << solve(i) << "\n";
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