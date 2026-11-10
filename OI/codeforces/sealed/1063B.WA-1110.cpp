// Problem : B. Labyrinth https://codeforces.com/problemset/problem/1063/B
// Time    : 2026-11-10 16:17:18
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
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

// f[x][y] = {l, r} -> left/right times
// stand at (x0, y), for each reachable point by up or down (x, y), f[x][y] = f[x0][y]
//          f[x + 1][y].r = min(f[x + 1][y].r, f[x][y].r), ((x + 1, y) can be reached), l is the same(use '-')
// Border: f[x][y] = {INF, INF}, f[r][c] = {0};
// Calculate: count of point with l and r fit problem's restriction
auto Main([[maybe_unused]] int C = 0) {
    int n, m, r, c, x, y;
    cin >> n >> m >> r >> c >> x >> y;
    vector<vi> a(n + 1, vi(m + 1)), f(n + 1, vi(m + 1, 1 << 30)), vis(n + 1, vi(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            a[i][j] = ch == '*';
        }
    }
    f[r][c] = 0;
    queue<pii> q;
    q.push({r, c});
    while (!q.empty()) {
        auto [u, v] = q.front();
        q.pop();
        if (vis[u][v]) continue;
        vi lst(1, u);
        for (int i = u - 1; i && !a[i][v]; i--) {
            lst.push_back(i);
        }
        for (int i = u + 1; i <= n && !a[i][v]; i++) {
            lst.push_back(i);
        }
        for (int i : lst) {
            f[i][v] = f[u][v];
            vis[i][v] = 1;
            if (v > 1 && !a[i][v - 1]) f[i][v - 1] = min(f[i][v - 1], f[i][v] + 1), q.push({i, v - 1});
            if (v < n && !a[i][v + 1]) f[i][v + 1] = min(f[i][v + 1], f[i][v]), q.push({i, v + 1});
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += f[i][j] <= x && f[i][j] + j - c <= y;
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
