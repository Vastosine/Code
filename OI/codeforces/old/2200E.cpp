// Problem : E. Divisive Battle https://codeforces.com/problemset/problem/2200/E
// Time    : 2026-10-17 12:54:28
#include <cstdio>
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

vi is;

vi getPrimes(int n) {
    vi ans;
    is.assign(n + 1, true);
    is[0] = is[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (!is[i]) continue;
        for (int j = i * 2; j <= n; j += i) {
            is[j] = false;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (is[i]) ans.push_back(i);
    }
    return ans;
}

vi primes = getPrimes(1e6);

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    bool increase = true;
    for (int i = 1; i < n; i++) increase &= a[i] >= a[i - 1];
    if (increase) return false;
    for (int &x : a) {
        if (is[x] || x <= 1) continue;
        for (int p : primes) {
            if (x % p) continue;
            while (x % p == 0) x /= p;
            if (x > 1) return true;
            x = p;
            break;
        }
    }
    increase = true;
    for (int i = 1; i < n; i++) increase &= a[i] >= a[i - 1];
    return !increase;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << (string[2]){"Bob", "Alice"} [solve()] << "\n";
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