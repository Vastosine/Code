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

auto solve() {
    int n;
    string s;
    cin >> n >> s;
    if (s[0] == '0') return -1ll;
    int ans = 1;
    for (int i = 1, c = 1, k = 0; i < n; i++, c++) {
        if (i < n && s[i] == '0' && s[i] == s[i - 1]) return -1ll;
        // if (s[i] != '0' && s[i - 1] != '0') ans = std::max(2ll, ans);
        if (i >= n || s[i] != s[i - 1]) {
            int K = i < n && s[i] != '0' && s[i - 1] != '0';
            if (K || c % 2 == 0) ans = std::max(2ll, ans);
            if (k && K && c == 2) ans = 3;
            k = K;
            c = 0;
        }
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