// Problem : E. Idiot First Search https://codeforces.com/problemset/problem/2195/E
// Time    : 2026-10-17 21:52:08
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

vector<vi> s;
vi m, a;

int dfs(int u = 1) {
    m[u] = 1;
    for (int v : s[u]) {
        if (v) m[u] += dfs(v);
    }
    return m[u];
}

const int M = 1e9 + 7;
void dfs(int u, int sum = 0) {
    a[u] = (sum + 2 * m[u] - 1) % M;
    for (int v : s[u]) if (v) dfs(v, a[u]);
}


auto solve() {
    int n;
    cin >> n;
    s.assign(n + 1, vi(2));
    assign(n + 1, m, a);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    dfs();
    dfs(1, 0);
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
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