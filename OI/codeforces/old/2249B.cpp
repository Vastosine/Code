// Problem : B. Permutation Cuts https://codeforces.com/problemset/problem/2249/B
// Time    : 2026-10-19 16:43:34
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

vi MUL(2, 1);
int mul(int n) {
    if (n < MUL.size()) return MUL[n];
    int ans = MUL.back();
    for (int i = MUL.size(); i <= n; i++) {
        MUL.push_back(ans = ans * i % M);
    }
    return MUL[n];
}

int solve() {
    int n;
    cin >> n;
    vi a(n - 1);
    cin >> a;
    int t = a.back();
    for (int i = 1, k = 0; i < n - 1; i++) {
        if (a[i] < a[i - 1] && !k) k = 1, t = a[i - 1];
        if (k && a[i] > a[i - 1]) return 0;
    }
    if (t != n - 1) return 0;
    if (a[0] == a.back() && a[0] == n - 1) return mul(n - 2) * 2 % M;
    if (a[0] == a.back()) return 0;
    vi vis(n + 1);
    int l = 0, r = n - 2, ans = 2, L = 1 + (a[0] > a.back()), R = 1 + (a[0] < a.back());
    vis[a[l]] = vis[a[r]] = 1;
    while (l < r) {
        if (a[l] == a[r] && a[l] < n - 1) return 0;
        if (a[l] == a[r]) {
            ans *= mul(r - l);
            ans %= M;
            break;
        }
        if (a[l] > a[r]) {
            while (a[r] == a[r - 1] && l < r) 
                r--, (ans *= a[r] - R++) %= M, L++;
            if (a[r] < R) return 0;
            if (!vis[a[r - 1]] && a[r - 1] < a[l]) L++;
            vis[a[r - 1]] = 1;
            for (int i = a[r] + 1; l < r && i <= a[r - 1]; i++) R += vis[i];
            r--;
        } else {
            while (a[l] == a[l + 1] && l < r) 
                l++, (ans *= a[l] - L++) %= M, R++;
            if (a[l] < L) return 0;
            if (!vis[a[l + 1]] && a[l + 1] < a[r]) R++;
            vis[a[l + 1]] = 1;
            for (int i = a[l] + 1; l < r && i <= a[l + 1]; i++) L += vis[i];
            l++;
        }
        ans %= M;
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