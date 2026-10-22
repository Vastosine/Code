// Problem : F1. XOR Transformations (Easy Version) https://codeforces.com/problemset/problem/2267/F1
// Time    : 2026-10-19 14:35:11
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
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    sort(a);
    vi f(64);
    f[0] = a.back() - a.front();
    for (int i = 1; i < 64 && a.back(); i++) {
        vi tmp;
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                tmp.push_back(a[l] ^ a[r]);
            }
        }
        sort(tmp);
        for (int j = 0; j < n; j++) a[j] = tmp[j];
        f[i] = a.back() - a.front();
    }
    while (m--) {
        int x;
        cin >> x;
        if (x > 63) cout << "0\n";
        else cout << f[x] << "\n";
    }
    return 0ll;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    // while (c--) {
    //     vi ans = solve();
    //     if (ans.empty()) cout << "NO";
    //     else cout << "YES\n" << ans << "\n";
    // }
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}