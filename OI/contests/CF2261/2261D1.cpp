// Problem : D1. Come Be My Friend, Don't Be So Scared (Easy Version) https://codeforces.com/contest/2261/problem/D1
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

using vpii = vector<pii>;

vector<vpii> b(32);
const vpii &build(int k) {
    if (!b[k].empty()) return b[k];
    if (k == 2) return b[k] = {{2, 3}};
    vpii t;
    t = b[k] = build(k - 1);
    int p = 1 << (k - 1);
    b[k].push_back({1 + p / 2, p / 2 * 3});
    for (auto &[x, y] : t) {
        b[k].push_back({x + p, y + p});
    }
    return b[k];
}

vpii f(int k, int dx = 0) {
    if (k == 0 || k == 1) return {{1 + dx, 1 + dx}};
    vpii ans = {{1 + dx, (1 << (k - 1)) + dx}};
    const auto &t = build(k);
    for (auto &[u, v] : t) ans.push_back({u + dx, v + dx});
    return ans;
}

vpii solve() {
    int n, m;
    cin >> n >> m;
    if (n == 1) return {};
    if (n == 2) return {{1, 1}};
    if (n == 3) return {{1, 1}, {2, 2}};
    vpii ans;
    for (int s = 0, k = 0; s < n; k++) {
        int y = 1ll << k;
        if (n & y) {
            vpii t = f(k, s);
            s += y;
            for (auto &[u, v] : t) ans.push_back({u, v});
        }
    }
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // auto p = f(4, 2);
    // for (auto &[u, v] : p) cout << u << " " << v << "\n";
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) {
        auto ans = solve();
        cout << ans.size() << "\n";
        for (auto &[i, j] : ans) cout << i << " " << j << "\n";
    }
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}