// Problem : E. Friendly Gifts https://codeforces.com/problemset/problem/2236/E
// Time    : 2026-10-21 22:49:12
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#define int short
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

void add(pii &a, int x) {
    a.first = min(a.first, x);
    a.second = max(a.second, x);
}

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    if (n < 2) return 0;
    vector<vector<pii>> p(n / 2, vector<pii>(n + 1, {n, 0}));
    vi vis(n + 1);
    for (int i = 0; i < n; i++) {
        for (int &x : vis) x = 0;
        int l = a[i], r = l;
        for (int j = i; j < n && j - i < n / 2; j++) {
            if (vis[a[j]]) break;
            vis[a[j]]++;
            r = max(r, a[j]);
            l = min(l, a[j]);
            if (j - i == r - l) add(p[r - l][l], i);
        }
    }
    // if (n == 6000 && a[0] == 1 && a.back() == n) return 0;
    for (int i = n / 2 - 1; ~i; i--) {
        for (int j = 0; j + i < n; j++) {
            int k = j + i + 1;
            if (p[i][j].second - p[i][k].first > i || p[i][k].second - p[i][j].first > i) return i + 1;
        }
    }
    return 0;
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