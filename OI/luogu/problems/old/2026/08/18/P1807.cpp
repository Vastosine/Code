// Problem : P1807 最长路 https://www.luogu.com.cn/problem/P1807
// Time    : 2026-08-18 17:47:33

#include <algorithm>
#include <iostream>
#include <vector>
#define int long long

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

struct E {
    int v, w;
    bool operator<(const E &e) {
        return w < e.w;
    }
};

vector<vector<E>> e;
vi vis, dis;
using std::max;
int dfs(int u, int end) {
    if (u == end) return 0;
    if (vis[u]) return dis[u];
    int ans = -1e9;
    vis[u] = true;
    for (E ed : e[u]) {
        int v = ed.v, w = ed.w;
        ans = max(ans, dfs(v, end) + w);
    }
    return dis[u] = ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    e.assign(n + 1, {});
    vis.assign(n + 1, {});
    dis.assign(n + 1, -1e9);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
    }
    dfs(1, n);
    cout << (dis[1] <= -1e8 ? -1 : dis[1]);
}

#undef int
int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}