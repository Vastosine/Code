// Problem : C. Median Partition https://codeforces.com/problemset/problem/2222/C
// Time    : 2026-10-16 19:05:16
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

int median(const vi &a) {
    vi b = a;
    sort(b);
    return b[a.size() / 2];
}

auto solve() {
    int n;
    cin >> n;
    vi a(n + 1), s[3] = {a, a, a}, dp(n + 1, -n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int x = median(a);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) s[j][i] = s[j][i - 1];
        s[a[i] == x ? 1 : 2 * (a[i] > x)][i]++;
    }
    auto check = [&] (int l, int r) {
        return std::abs((s[0][r] - s[0][l - 1]) - (s[2][r] - s[2][l - 1])) <= s[1][r] - s[1][l - 1];
    };
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = !(i % 2); j < i; j += 2) {
            if (check(j + 1, i)) 
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }
    return dp[n];
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