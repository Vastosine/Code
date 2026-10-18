// Problem : E. What Does the Cow Say? https://codeforces.com/contest/2261/problem/E
// Time    : 2026-10-17 22:36:10
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

auto solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    vector<vi> a;
    for (int i = 1, t = 1; i < n; i++, t++) {
        if (s[i] != s[i - 1]) {
            if (s[i] == ')') a.push_back({});
            a.back().push_back(t);
            t = 0;
        }
        if (i == n - 1) a.back().push_back(t + 1);
    }
    int m = a.size(), ans = 0;
    vi b(m + 1), c(m + 1);
    for (int i = 1; i <= m; i++) {
        b[i] = a[i - 1][0] + b[i - 1];
        c[i] = a[i - 1][1] + c[i - 1];
        ans = max(ans, a[i - 1][0]);
        if (b[i] - b[1] <= k) ans = max(ans, b[i]);
    }
    if (!k) return ans;
    auto cost = [&] (int l, int r) { return c[r - 1] - c[l - 1];};
    auto f = [&] (int l, int r) { return b[r] - b[l - 1] - cost(l, r); };
    for (int i = 2, j = i + 1; i <= m && j <= m; i++) {
        while (cost(i, j + 1) <= k && j < m) j++;
        ans = max(ans, f(i, j));
    }
    return ans;
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