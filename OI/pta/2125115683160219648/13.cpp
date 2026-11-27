#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

vst Dijkstra(szt s, szt n, const vector<vector<pst>> &e) {
    vb vis(n + 1, 0);
    vst dis(n + 1, INF);
    dis[s] = 0;
    priority_queue<pst> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : e[u]) {
            auto nd = w + dis[u];
            if (nd < dis[v]) {
                dis[v] = nd;
                q.push({-nd, v});
            }
        }
    }
    return dis;
}

auto Main(int = 0) {
    szt n, m, q;
    cin >> n >> m >> q;
    vector<vector<pst>> e[2] = {};
    assign(n + 1, e[0], e[1]);
    while (m--) {
        szt u, v, c, d;
        cin >> u >> v >> c >> d;
        e[0][u].push_back({v, c});
        e[1][v].push_back({u, d});
    }
    vst dis[2] = {Dijkstra(1, n, e[0]), Dijkstra(n, n, e[1])};
    set<pst> s;
    vst res(n + 1);
    vst a(n + 1);
    for (szt i = 1; i <= n; i++) cin >> a[i];
    auto cost = [&] (szt t) {
        if (dis[0][t] == INF || dis[1][t] == INF) return (szt) INF;
        return dis[0][t] + (dis[1][t] + a[t] - 1) / a[t];
    };
    for (szt i = 1; i <= n; i++) {
        szt c = cost(i);
        s.insert({c, i});
        res[i] = c;
    }
    while (q--) {
        szt i, x;
        cin >> i >> x;
        auto it = s.find({res[i], i});
        s.erase(it);
        a[i] = x;
        szt c = cost(i);
        res[i] = c;
        s.insert({c, i});
        cout << s.begin()->first << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
