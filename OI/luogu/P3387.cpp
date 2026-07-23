#include <iostream>
#include <stack>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::stack;
using std::min;
using std::max;

int n, m, dfn_cnt, col_cnt;
vector<int> a, vis, low, dfn, in_stack, col, A, max_val;
vector<vector<int>> e, E;
stack<int> s;

void dfs(int u) {
    if (vis[u]) return;
    low[u] = dfn[u] = ++dfn_cnt;
    in_stack[u] = vis[u] = 1;
    s.push(u);
    for (int v : e[u]) {
        if (!vis[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int v;
        col[u] = ++col_cnt;
        while (!s.empty() && dfn[v = s.top()] >= dfn[u]) {
            s.pop();
            in_stack[v] = 0;
            col[v] = col[u];
        }
    }
}

int DFS(int u) {
    if (~max_val[u]) return max_val[u];
    max_val[u] = 0;
    for (int v : E[u]) {
        max_val[u] = max(max_val[u], DFS(v));
    }
    return max_val[u] += A[u];
}

int main() {
    cin >> n >> m;
    a.assign(n + 1, 0);
    vis.assign(n + 1, 0);
    low.assign(n + 1, 0);
    in_stack.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    col.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    e.assign(n + 1, vector<int>());
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i);
    }
    E.assign(col_cnt + 1, vector<int>());
    A.assign(col_cnt + 1, 0);
    max_val.assign(col_cnt + 1, -1);
    for (int u = 1; u <= n; u++) {
        for (int v : e[u]) {
            if (col[u] != col[v])
                E[col[u]].push_back(col[v]);
        }
        A[col[u]] += a[u];
    }
    int ans = 0;
    for (int u = 1; u <= col_cnt; u++) {
        ans = max(ans, DFS(u));
    }
    cout << ans << "\n";
}