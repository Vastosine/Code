// Problem : P4009 汽车加油行驶问题 https://www.luogu.com.cn/problem/P4009
// Time    : 2026-11-24 10:00:53
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

auto Main([[maybe_unused]] int = 0) {
    ll n, k, A, B, C;
    cin >> n >> k >> A >> B >> C;
    vector<vi> a(n, vi(n));
    vector<vector<vll>> dis(n, vector<vll>(n, vll(k + 1, INF)));
    vector<vector<vi>> vis(n, vector<vi>(n, vi(k + 1, 0)));
    cin >> a;
    dis[0][0][k] = 0;
    priority_queue<vll> q;
    q.push({0, 0, 0, k});
    const int dir[][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    while (!q.empty()) {
        auto u = q.top();
        int x = u[1], y = u[2], f = u[3];
        q.pop();
        if (vis[x][y][f]) continue;
        vis[x][y][f] = 1;
        if (f != k && a[x][y]) {
            ll nd = dis[x][y][f] + A;
            if (nd < dis[x][y][k]) {
                dis[x][y][k] = nd;
                q.push({-nd, x, y, k});
            }
            continue;
        }
        if (!f) {
            ll nd = dis[x][y][f] + A + C;
            if (nd < dis[x][y][k]) {
                dis[x][y][k] = nd;
                q.push({-nd, x, y, k});
            }
            continue;
        }
        for (auto &[dx, dy] : dir) {
            int vx = x + dx, vy = y + dy;
            if (vx < 0 || vx >= n || vy < 0 || vy >= n) continue;
            ll nd = dis[x][y][f] + (vx + vy < x + y) * B;
            if (nd < dis[x][y][f - 1]) {
                dis[vx][vy][f - 1] = nd;
                q.push({-nd, vx, vy, f - 1});
            }
        }
    }
    ll ans = INF;
    // for (auto &i : dis) {
    //     for (auto &j : i) {
    //         ll res = *min_element(j.begin(), j.end());
    //         cout << (res == INF ? -1 : res) << " ";
    //     }
    //     cout << "\n";
    // }
    for (int i = 0; i <= k; i++) ans = min(ans, dis[n - 1][n - 1][i]);
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
