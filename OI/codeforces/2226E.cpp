// Problem : E. Mental Monumental (Hard Version) https://codeforces.com/contest/2226/problem/E
// Time    : 2026-10-13 11:15:13
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

bool check(const vi &a, int x) {
    vi b(x, -1);
    int k = 0;
    for (int i : a) {
        if (i < x && !~b[i]) b[i] = i;
        else {
            while (~b[k] && k < x) k++;
            if (2 * k < i && k < x) b[k] = i;
        }
    }
    for (int i : b) if (!~i) return false;
    return true;
}

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    vector<pii> p;
    for (int i = 0; i < n; i++) p.push_back({a[i], i});
    sort(a);
    sort(p);
    int l = 0, r = n + 1;
    while (l < r - 1) {
        int x = (l + r) >> 1;
        bool ans = check(a, x);
        if (ans) l = x;
        else r = x;
    }
    vi c, b(l, -1), ans(n);
    int k = 0;
    for (int i : a) {
        if (i < l && !~b[i]) b[i] = i, c.push_back(i + 1);
        else {
            while (~b[k] && k < l) k++;
            if (2 * k < i && k < l) b[k] = l, c.push_back(i - k);
            else c.push_back(1);
        }
    }
    for (int i = 0; i < n; i++) {
        ans[p[i].second] = c[i];
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