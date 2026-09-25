// Problem : G. Modular Tree https://codeforces.com/contest/2266/problem/G
// Time    : 2026-09-21 22:37:13

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

using std::gcd;

vector<vi> e;
vi a, b, vis, ans;

int dfs(int u = 1) {
    vis[u] = true;
    int d = b[u], son = 0, s = 0;
    for (int v : e[u]) {
        if (!vis[v]) {
            d = gcd(d, dfs(v));
            son++;
            s += a[v];
        }
    }
    d = gcd(d, s);
    if (!son || d == b[u]) return ans[u] = a[u], 0; 
    ans[u] = a[u] + (b[u] - a[u] - 1) / d * d;
    return d;
}

void solve() {
    int n;
    cin >> n;
    a.assign(n + 1, {});
    b.assign(n + 1, {});
    vis.assign(n + 1, {});
    e.assign(n + 1, {});
    ans.assign(n + 1, {});
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs();
    int out = 0;
    for (int i : ans) out += i;
    cout << out << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}