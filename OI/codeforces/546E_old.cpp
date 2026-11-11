// Problem : E. Soldier and Traveling https://codeforces.com/problemset/problem/546/E
// Time    : 2026-11-11 17:31:06
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
    int n, m, s = 0;
    cin >> n >> m;
    vi a, b, c, dep, to, cur;
    vector<vi> e;
    assign(n + 2, a, b, c, to, e);
    auto addEdge = [&] (int u, int v, int w) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    for (int i = 1; i <= n; i++) cin >> a[i], addEdge(0, i, a[i]);
    for (int i = 1; i <= n; i++) cin >> b[i], addEdge(i, n + 1, b[i]), s += b[i];
    while (m--) {
        int u, v, w = 1 << 30;
        cin >> u >> v;
        addEdge(u, v, w);
        addEdge(v, u, w);
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
                    if (c[j] && !dep[v]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, int lim = 1 << 30) {
                if (u == t || !lim) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    int id = e[u][cur[u]], v = to[id], w = c[id];
                    if (dep[v] != dep[u] + 1) continue;
                    int add = f(f, v, min(lim - ret, w));
                    ret += add;
                    c[id] -= add;
                    c[id ^ 1] += add;
                } 
                return ret;
            };
            ans += dfs(dfs, s);
        }
    };
    int ans = Dinic(0, n + 1);
    if (ans < s) return cout << "NO\n", 0;
    cout << "YES\n";
    vector<vi> res(n + 1, vi(n + 1));
    for (int u = 1; u <= n; u++) {
        res[u][u] += a[u];
        for (int i : e[u]) {
            if (i & 1) continue;
            int v = to[i], w = c[i ^ 1];
            if (!v || v == n + 1) continue;
            res[u][v] += w;
            res[u][u] -= w;
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            cout << res[u][v] << " ";
        }
        cout << "\n";
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
