// Problem : D. Signs of Prefix Sums https://codeforces.com/problemset/problem/2260/D
// Time    : 2026-10-19 14:57:24
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
using std::min;
using std::abs;

auto solve() {
    int n;
    string s;
    cin >> n >> s;
    vi a(n + 1);
    for (int i = 0; i < n; i++) a[i + 1] = s[i] == '0' ? 0 : s[i] == '+' ? 1 : -1;
    vector<vi> f(n + 1, vi(7, 100));
    f[0][3] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3 && (a[i] != '0' || j < 2); j++) {
            int k = j * a[i] + 3;
            for (int p = 0; p < 7; p++) {
                if (p == k) continue;
                f[i][k] = min(f[i][k], max(f[i - 1][p], abs(p - k)));
            }
        }
    }
    int ans = 10;
    for (int i : f[n]) ans = min(ans, i);
    return ans > 3 ? -1 : ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
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