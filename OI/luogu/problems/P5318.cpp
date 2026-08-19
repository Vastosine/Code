// Problem : P5318 【深基18.例3】查找文献 https://www.luogu.com.cn/problem/P5318
// Time    : 2026-08-18 17:48:04

#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::set;

vector<set<int>> e;
vector<int> vis;

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    cout << u << " ";
    for (int v : e[u]) {
        dfs(v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    e.assign(n + 1, {});
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].insert(v);
    }
    vis.assign(n + 1, 0);
    for (int i = 1; i <= 1; i++) {
        dfs(i);
    }
    cout << "\n";
    vis.assign(n + 1, 0);
    for (int i = 1; i <= 1; i++) {
        std::queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            cout << u << " ";
            for (int v : e[u]) {
                q.push(v);
            }
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}