// Problem : P1892 [BalticOI 2003] 团伙 (Day 2) https://www.luogu.com.cn/problem/P1892
// Time    : 2026-08-18 11:26:07

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

struct Edge {
    int v, w;
};

vector<vector<Edge>> e;
vi vis;
vector<vi> a;
int n, m;

void addEdge(int u, int v, int w, bool k = true) {
    if (k) e[u].push_back({v, w}), e[v].push_back({u, w});
    a[u][v] = a[v][u] = w;
}

void dfs(int r, int u) {
    vis[u] = true;
    for (Edge i : e[u]) {
        int v = i.v;
        if (!a[r][v] && a[r][u] == a[u][v]) addEdge(r, v, 1, 0);
        if (!vis[v] && a[u][v]) dfs(r, v);
    }
}

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    for (int v = 1; v <= n; v++) {
        if (u != v && a[u][v] == 1) dfs(v);
    }
}

void solve() {
    cin >> n >> m;
    e.assign(n + 1, {});
    a.assign(n + 1, vi(n + 1, 0));
    while (m--) {
        int u, v, w;
        char op;
        cin >> op >> u >> v;
        w = op == 'F' ? 1 : -1;
        addEdge(u, v, w);
    }
    for (int i = 1; i <= n; i++) {
        vis.assign(n + 1, {});
        dfs(i, i);
    }
    vis.assign(n + 1, {});
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans++;
            dfs(i);
        }
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}