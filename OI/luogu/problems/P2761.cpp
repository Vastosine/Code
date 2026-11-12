// Problem : P2761 软件补丁问题 https://www.luogu.com.cn/problem/P2761
// Time    : 2026-11-12 20:02:02
#include <iostream>
#include <queue>
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
    int n, m;
    cin >> n >> m;
    vi b1, b2, f1, f2;
    vll w;
    assign(m, b1, b2, f1, f2, w);
    auto check = [&] (int u, int f) {
        return (u & b2[f]) == b2[f] && (~u & b1[f]) == b1[f];
    };
    auto apply = [&] (int u, int f) {
        return (u | f1[f]) & ~f2[f];
    };
    for (int i = 0; i < m; i++) {
        cin >> w[i];
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            b1[i] |= (c == '+') << j;
            b2[i] |= (c == '-') << j;
        }
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            f2[i] |= (c == '+') << j;
            f1[i] |= (c == '-') << j;
        }
    }
    vll dis(1 << n, INF);
    vi vis(1 << n);
    dis[0] = 0;
    priority_queue<pll> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < m; i++) {
            if (check(u, i)) {
                int v = apply(u, i);
                ll nd = dis[u] + w[i];
                if (nd < dis[v]) {
                    dis[v] = nd;
                    q.push({-nd, v});
                }
            }
        }
    }
    ll ans = dis.back();
    return ans == INF ? 0 : ans;
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
