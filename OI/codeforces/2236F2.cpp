// Problem : F2. Elections in Saransk (hard version) https://codeforces.com/problemset/problem/2236/F2
// Time    : 2026-10-21 18:49:45
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <map>
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

vi primes = getPrimes(5e5);

const int M = 1e9 + 7;

using std::lcm;

int dfs(const vi &a, int L, int l = 1, int s = 1, int i = 0) {
    if (i == a.size()) return l * L == s;
    int ans = 0;
    for (int j = 1; j <= a[i]; j++) {
        if (a[i] % j) continue;
        ans += dfs(a, L, lcm(l, j), s * j, i + 1);
    }
    return ans % M;
}

int F(vi a, int K) {
    int n = a.size();
    if (!n) return 1;
    sort(a);
    vector<vector<vi>> f(2, vector<vi>(a.back() + 1, vi(a.back() + 1 + K)));
    // f[0].assign(a[0] + 1, vi(a[0] + 1));
    for (int i = 0; i <= a[0]; i++) {
        f[0][i][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        // f[i].assign(a[i] + 1, vi(a[i] + K + 1));
        for (int j = 0; j <= a[i]; j++) {
            for (int k = j; k <= a[i] + K; k++) {
                f[i % 2][j][k] = 0;
                for (int t = 0; t <= a[i] && t <= k && t <= j; t++) {
                    (f[i % 2][j][k] += f[(i + 1) % 2][j][k - t]) %= M;
                }
                for (int t = 0; t < j; t++) {
                    (f[i % 2][j][k] += f[(i + 1) % 2][t][k - j]) %= M;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= a.back(); i++) {
        (ans += f[(n + 1) % 2][i][i + K]) %= M;
    }
    return ans;
}

auto solve() {
    int n, x;
    cin >> n >> x;
    vi a(n);
    cin >> a;
    std::map<int, vi> c;
    for (int i : a) {
        for (int p : primes) {
            if (i < p) break;
            if (is[i]) {
                c[i].push_back(1);
                break;
            }
            if (i % p) continue;
            int t = 0;
            while (i % p == 0) i /= p, t++;
            c[p].push_back(t);
        }
    }
    int ans = 1;
    for (auto &[p, lst] : c) {
        int c = 0;
        while (x % p == 0) x /= p, c++;
        (ans *= F(lst, c)) %= M;
    }
    if (x > 1) return 0ll;
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