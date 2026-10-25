// Problem : E. Kirei Attacks the Estate https://codeforces.com/problemset/problem/2114/E
// Time    : 2026-10-25 18:48:11
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

int n;
vector<vi> e;
vi f, g;
vector<ll> dp, a;

void dfs(int u = 1, int fa = 0) {
    f[u] = fa;
    g[u] = f[fa];
    dp[u] = a[u];
    if (g[u]) {
        dp[u] += max(0ll, dp[g[u]] - a[f[u]]);
    }
    for (int v : e[u]) {
        if (v != 1 && !f[v]) dfs(v, u);
    }
}

auto solve() {
    cin >> n;
    assign(n + 1, e, f, g, dp, a);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs();
    for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}