// Problem : B. Labyrinth https://codeforces.com/problemset/problem/1063/B
// Time    : 2026-11-11 08:21:38
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, r, c, x, y;
    cin >> n >> m >> r >> c >> x >> y;
    vector<vi> f(n + 1, vi(m + 1, 1 << 30)), a(n + 1, vi(m + 1)), vis(n + 1, vi(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            a[i][j] = ch == '*';
        }
    }
    deque<pii> q;
    q.push_back({r, c});
    const int tr[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int ans = 0;
    f[r][c] = 0;
    while (!q.empty()) {
        auto [u, v] = q.front();
        q.pop_front();
        if (a[u][v] || vis[u][v]) continue;
        vis[u][v] = 1;
        ans += f[u][v] <= x && f[u][v] + v - c <= y;
        for (auto &[dx, dy] : tr) {
            int nu = u + dx, nv = v + dy;
            if (nu > 0 && nu <= n && nv > 0 && nv <= m && !a[nu][nv]) {
                if (dy == -1) q.push_back({nu, nv}), f[nu][nv] = min(f[nu][nv], f[u][v] + 1);
                else q.push_front({nu, nv}), f[nu][nv] = min(f[nu][nv], f[u][v]);
            }
        }
    }
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
