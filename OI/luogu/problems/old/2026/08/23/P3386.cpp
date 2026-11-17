// Problem : P3386 【模板】二分图最大匹配 https://www.luogu.com.cn/problem/P3386
// Time    : 2026-08-23 07:00:58

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vector<vi> e[2], w;
vi vis[2], count[2], match;
using std::min;

int dfs(int u, int c, int s = 0) {
    if (s == 1 && match[u] < count[s][u]) {
        int x = min(count[s][u] - match[u], c);
        match[u] += x;
        return x;
    }
    if (!c) return 0;
    if (vis[s][u]) return 0;
    vis[s][u] = true;
    int ret = 0;
    for (int v : e[s][u]) {
        int &x = s ? w[v][u] : w[u][v];
        int y = dfs(v, s ? min(c, x) : c, !s);
        ret += y;
        c -= y;
        x -= y * (2 * s - 1);
    }
    return ret;
}

void solve() {
    int n, m, en;
    cin >> n >> m >> en;
    e[0].assign(n, {});
    e[1].assign(m, {});
    count[0].assign(n, 1);
    count[1].assign(m, 1);
    match.assign(m, {});
    w.assign(n, vi(m));
    while (en--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        e[0][u].push_back(v);
        e[1][v].push_back(u);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vis[0].assign(n, {});
        vis[1].assign(m, {});
        ans += dfs(i, count[0][i]);
    }
    cout << ans << "\n";
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}