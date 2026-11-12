// Problem : P2756 飞行员配对方案问题 https://www.luogu.com.cn/problem/P2756
// Time    : 2026-11-12 19:05:35
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
    int n, m;
    cin >> m >> n;
    vector<vi> e(n + 2);
    vi to, c, cur, dep;
    int s = 0, t = n + 1;
    auto addEdge = [&] (int u, int v, int w) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    for (int i = 1; i <= m; i++) {
        addEdge(s, i, 1);
    }
    for (int i = m + 1; i <= n; i++) {
        addEdge(i, t, 1);
    }
    while (true) {
        int u, v;
        cin >> u >> v;
        if (!~u) break;
        addEdge(u, v, 1);
    }
    auto Dinic = [&] (int s, int t) {
        int ans = 0;
        while (true) {
            assign(n + 2, dep, cur);
            dep[s] = 1;
            vi o(1, s);
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    int v = to[j];
                    if (!dep[v] && c[j]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, int lim = 1 << 30) {
                if (!lim || u == t) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    int i = e[u][cur[u]], v = to[i];
                    if (dep[v] == dep[u] + 1) {
                        int add = f(f, v, min(lim - ret, c[i]));
                        ret += add;
                        c[i] -= add;
                        c[i ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    };
    int ans = Dinic(s, t);
    cout << ans << "\n";
    for (int u = 1; u <= m; u++) {
        for (int i : e[u]) {
            int v = to[i];
            if (c[i ^ 1] && v > m && v <= n) cout << u << " " << v << "\n";
        }
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
