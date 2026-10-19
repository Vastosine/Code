// Problem : C. Monopati https://codeforces.com/problemset/problem/2163/C
// Time    : 2026-10-19 12:23:24
#include <iostream>
#include <set>
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

pii &operator+=(pii &p, int x) { return p = { std::min(p.first, x), std::max(p.second, x) }; }

pii &operator+=(pii &p, const pii &q) { return (p += q.first) += q.second; }

auto solve() {
    int n;
    cin >> n;
    vector<vi> a(2, vi(n));
    cin >> a;
    vi vis(2 * n + 1), low(2 * n + 1);
    int ans = 0;
    std::multiset<int> s(a[1].begin(), a[1].end());
    for (int i = 0; i < n; i++) {
        s.insert(a[0][i]);
        int l = *s.begin(), r = *--s.end();
        low[r] = std::max(low[r], l);
        // ans = std::max(ans, l * (2 * n - r + 1));
        s.erase(s.find(a[1][i]));
    }
    for (int r = 1; r <= 2 * n; r++) {
        low[r] = std::max(low[r], low[r - 1]);
        ans += low[r];
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