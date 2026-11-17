// Problem : U721285 Minecraft Shapeless Matches https://www.luogu.com.cn/problem/U721285
// Time    : 2026-08-23 08:22:32

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
    int n, m;
    cin >> n >> m;
    e[0].assign(n, {});
    e[1].assign(m, {});
    count[0].assign(n, {});
    count[1].assign(m, {});
    match.assign(m, {});
    w.assign(n, vi(m));
    cin >> count[0] >> count[1];
    for (int u = 0; u < n; u++) {
        int tn;
        cin >> tn;
        while (tn--) {
            int v;
            cin >> v;
            e[0][u].push_back(v);
            e[1][v].push_back(u);
        }
    }
    bool ans = true;
    for (int i = 0; i < n; i++) {
        vis[0].assign(n, {});
        vis[1].assign(m, {});
        ans &= dfs(i, count[0][i]) == count[0][i];
    }
    cout << ans << "\n";
}

int main() {
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}