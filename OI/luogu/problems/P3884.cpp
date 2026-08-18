// Problem : P3884 [JLOI2009] 二叉树问题 https://www.luogu.com.cn/problem/P3884
// Time    : 2026-08-05 20:14:30

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vector<vector<int>> e; 
vector<int> vis, dep, fa, nodes;

void dfs(int u = 1, int depth = 0) {
    vis[u] = true;
    while (depth >= nodes.size()) nodes.push_back(0);
    nodes[depth]++;
    dep[u] = depth;
    for (int v : e[u]) {
        if (vis[v]) continue;
        fa[v] = u;
        dfs(v, depth + 1);
    }
}

void solve() {
    int n;
    cin >> n;
    e.assign(n + 1, {});
    vis.assign(n + 1, {});
    dep.assign(n + 1, {});
    fa.assign(n + 1, {});
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs();
    int height = nodes.size();
    int width = 0;
    for (int i : nodes) {
        width = std::max(width, i);
    }
    int dis = 0;
    int u, v;
    cin >> u >> v;
    int U = u, V = v;
    if (dep[u] < dep[v]) std::swap(u, v);
    while (dep[u] > dep[v]) {
        u = fa[u];
    }
    while (u != v) {
        u = fa[u];
        v = fa[v];
    }
    cout << height << "\n" << width << "\n" << 2 * (dep[U] - dep[u]) + dep[V] - dep[u];
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}