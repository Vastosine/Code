// Problem : SBR：荒野中的觉悟 https://ac.nowcoder.com/acm/contest/142131/I
// Time    : 2026-10-18 16:19:28
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

const int M = 998244353;

int pow(int x, int n) {
    return n ? pow(x * x % M, n / 2) * (n % 2 ? x : 1) % M : 1;
}

int inv(int x) {
    return pow(x, M - 2);
}

const int inv100 = inv(100);

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int s = 1, ans = 0, p = inv(n - 1);
    if (n == 2) return (200 - a[0] - a[1]) * inv100 % M;
    for (int &i : a) {
        i = (M + 1 - i * p % M * inv100 % M) % M;
        (s *= i) %= M;
    }
    for (int i : a) {
        (ans += s * inv(i) % M) %= M;
    }
    return (ans + M) % M;
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