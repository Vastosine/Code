// Problem : F. Anya Loves Trees! https://codeforces.com/problemset/problem/2244/F
// Time    : 2026-10-20 10:56:26
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

int n;
vector<vi> s, r;
vi l;

using std::min;
using std::max;

bool dfs(int u) {
    if (!r[u].empty()) return true;
    r[u] = {n, 0};
    vi p;
    int q = 0, m = s[u].size();
    for (int v : s[u]) {
        if (!dfs(v)) return false;
        l[u] += l[v];
        r[u][0] = min(r[u][0], r[v][0]);
        r[u][1] = max(r[u][1], r[v][1]);
        p.push_back(r[v][0]);
        if (p.back() < p[q]) q = p.size() - 1;
    }
    if (l[u] != r[u][1] - r[u][0] + 1) return false;
    for (int i = 1; i < m; i++) {
        if (p[(q + i) % m] < p[(q + i - 1) % m]) return false;
    }
    return true;
}

auto solve() {
    cin >> n;
    assign(n + 1, s, l, r);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        s[p].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x) r[i] = {x, x}, l[i] = 1;
    }
    return dfs(1);
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
    // while (c--) solve();
    const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}