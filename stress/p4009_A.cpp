// pasted
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll;
[[maybe_unused]] const ll INF = 1ll << 60;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename A, typename B> istream &operator>>(istream &in, vector<vector<A>> &a) { for (auto &r : a) in >> r; return in; }
void init() {}
auto Main(int = 0) {
    ll n, k, A, B, C;
    cin >> n >> k >> A >> B >> C;
    vector<vi> a(n, vi(n));
    vector<vector<vll>> dis(n, vector<vll>(n, vll(k + 1, INF)));
    vector<vector<vi>> vis(n, vector<vi>(n, vi(k + 1, INF)));
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
            if (nd < dis[x][y][k]) { dis[x][y][k] = nd; q.push({-nd, x, y, k}); }
        }
        if (!f) {
            ll nd = dis[x][y][f] + A + B;
            if (nd < dis[x][y][k]) { dis[x][y][k] = nd; q.push({-nd, x, y, k}); }
        }
        if (f) for (auto &[dx, dy] : dir) {
            int vx = x + dx, vy = y + dy;
            if (vx < 0 || vx >= n || vy < 0 || vy >= n) continue;
            ll nd = dis[x][y][f] + (vx + vy < x + y) * C;
            if (nd < dis[x][y][f - 1]) { dis[vx][vy][f - 1] = nd; q.push({-nd, vx, vy, f - 1}); }
        }
    }
    ll ans = INF;
    for (int i = 0; i <= k; i++) ans = min(ans, dis[n - 1][n - 1][i]);
    return ans;
}
int main() { ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); init(); auto ans = Main(0); cout << ans << "\n"; return 0; }
