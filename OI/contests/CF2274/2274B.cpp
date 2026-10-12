// Problem : B. Prefix https://codeforces.com/contest/2274/problem/B
// Time    : 2026-10-12 07:59:59
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
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
template<typename F, typename T, typename... Args> T update(F &&f, T &x, Args &&...args) { return ((x = f(x, args)), ...), x; }
template<typename F, typename T, typename... Args> T func(F &&f, const T &x, Args &&...args) { T tmp(x); return ((tmp = f(tmp, args)), ...), tmp; }
int abs(int x) { return x < 0 ? -x : x; }

int max(int x, int y) { return std::max(x, y); }
int min(int x, int y) { return std::min(x, y); }

int max_abs(int x, int y) { return abs(x) < abs(y) ? y : x; }

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    // vi l = a, r = a;
    int ans = a[0];
    for (int i = 1, s = a[0], t = a[0]; i < n; i++) {
        update(max, ans, a[i], a[i] + s, a[i], a[i] - t);
        s = func(max, a[i], a[i] + s, a[i] + s * 2);
        t = func(min, a[i], a[i] + t, a[i] + t * 2);
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
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}