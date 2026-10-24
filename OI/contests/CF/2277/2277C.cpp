// Problem : Edge Addeleting https://m1.codeforces.com/contest/2277/problem/C
// Time    : 2026-10-24 19:05:14
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

int n, m;
vector<vi> e, dis;
vi vis, dep, ans;

void dfs(int u = 1, int d = 0) {
    dep[u] = d;
    for (int v : e[u]) {
        if (v == 1 || dep[v]) continue;
        dfs(v, d + 1);
        int y = dis[v][0] + 1;
        if (y > dis[u][0]) dis[u][1] = dis[u][0], dis[u][0] = y;
        else if (y > dis[u][1]) dis[u][1] = y;
    }
}

// int max2(int x, int y, int z) {
//     return x + y + z - min({x, y, z});
// }

void dfs2(int u, int fd = 0) {
    ans[u] = max({dis[u][0], dis[u][1], fd});
    for (int v : e[u]) {
        if (dep[v] == dep[u] + 1) {
            dfs2(v, 1 + max(fd, dis[u][dis[u][0] == dis[v][0] + 1]));
        }
    }
}

auto solve() {
    cin >> n >> m;
    assign(n + 1, e, dep, ans);
    dis.assign(n + 1, vi(2));
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    set<int> s(e[1].begin(), e[1].end());
    while (m--) {
        int x;
        cin >> x;
        s.insert(x);
    }
    dfs();
    for (int u : e[1]) {
        dfs2(u);
    }
    // cout << ans << "\n";
    int ret = 0;
    for (int i : s) {
        ret = max(ans[i], ret);
    }
    return ret + 1;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}