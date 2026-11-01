// Problem : P17832 [CSP-S 2026] 地铁 / subway（民间数据） https://www.luogu.com.cn/problem/P17832?contestId=369912
// Time    : 2026-11-01 19:57:13
#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}
int c, n, m, d, q;
vector<vector<pair<ll, ll>>> e, cost;
vector<ll> W;
vector<vector<ll>> dir, dis;

void addEdge(int u, int v, ll w) {
    e[u].push_back({v, w});
    e[v].push_back({u, w});
}

vector<ll> Dij(int U) {
    vector<ll> di(n + 1, INF), vis(n + 1);
    di[U] = 0;
    priority_queue<pair<ll, ll>> q;
    q.push({0, U});
    while (!q.empty()) {
        auto [_, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &[v, w] : e[u]) {
            if (vis[v]) continue;
            di[v] = min(di[v], di[u] + w);
            q.push({-di[v], v});
        }
    }
    return di;
}

ll read() {
    char ch;
    while ((ch = getchar()) && (ch < '0' || ch > '9'));
    ll x = 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

auto Main([[maybe_unused]] int C = 0) {
    c = read();
    n = read();
    m = read();
    d = read();
    q = read();
    // cin >> c >> n >> m >> d >> q;
    assign(n + 1, e, dis);
    dir.assign(n + 1, vector<ll>(n + 1, INF));
    assign(m + 1, W, cost);
    for (int i = 1; i <= m; i++) W[i] = read();
    for (int i = 1; i <= n; i++) {
        int k = read();
        for (int j = 0; j < k; j++) {
            ll x = read(), w = read();
            // cin >> x >> w;
            cost[x].push_back({i, w});
        }
    }
    // int mx = 0;
    for (int i = 1; i <= m; i++) {
        // mx = max(mx, (int)cost[i].size());
        for (auto &[u, x] : cost[i]) {
            for (auto &[v, y] : cost[i]) {
                if (u != v) dir[u][v] = dir[v][u] = min(dir[u][v], x + y);
            }
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (dir[u][v] < INF) addEdge(u, v, dir[u][v]);
        }
    }
    // cout << mx;
    for (int u = 1; u <= n; u++) {
        dis[u] = Dij(u);
        // cout << dis[u] << "\n";
    }
    while (q--) {
        int x, y;
        x = read();
        y = read();
        ll ans = INF;
        for (auto &[u, w1] : cost[x]) {
            for (auto &[v, w2] : cost[y]) {
                ans = min(ans, w1 + w2 + dis[u][v]);
            }
        }
        cout << ans + W[x] + W[y] << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
