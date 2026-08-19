// Problem : P2853 [USACO06DEC] Cow Picnic S https://www.luogu.com.cn/problem/P2853
// Time    : 2026-08-18 17:47:34

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int k, n, m;
vector<vi> e, vis;
vi a;

void dfs(int r, int u) {
    if (vis[r][u]) return;
    vis[r][u] = true;
    for (int v : e[u]) {
        dfs(r, v);
    }
}

void solve() {
    cin >> k >> n >> m;
    a.assign(k, {});
    e.assign(n + 1, {});
    vis.assign(n + 1, vi(n + 1, 0));
    cin >> a;
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, i);
        // for (int j = 1; j <= n; j++) cout << vis[i][j] << " ";
        // cout << "\n";
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        bool k = true;
        for (int j : a) {
            k &= vis[j][i];
        }
        ans += k;
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}