// Problem : E. Soldier and Traveling https://codeforces.com/problemset/problem/546/E
// Time    : 2026-11-11 18:27:38
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

const int inf = 1 << 30;

vector<vi> Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> e;
    vi to, c, a, b, dep, cur;
    int s1 = 0, s2 = 0;
    int s = 0, t = 2 * n + 1;
    assign(2 * n + 2, e, to, c, a, b);
    
    auto addEdge = [&] (int u, int v, int w = inf) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    for (int i = 1; i <= n; i++) cin >> a[i], s1 += a[i], addEdge(s, i, a[i]);
    for (int i = 1; i <= n; i++) cin >> b[i], s2 += b[i], addEdge(i + n, t, b[i]);
    for (int i = 1; i <= n; i++) addEdge(i, i + n, inf);
    while (m--) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v + n, inf);
        addEdge(v, u + n, inf);
    }
    if (s1 != s2) return {};
    auto Dinic = [&] (int s, int t) {
        int ans = 0;
        while (true) {
            assign(2 * n + 2, dep, cur);
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
            auto dfs = [&] (auto &&f, int u, int lim = inf) {
                if (!lim || u == t) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    int id = e[u][cur[u]], v = to[id], w = c[id];
                    if (dep[v] == dep[u] + 1) {
                        int add = f(f, v, min(lim - ret, w));
                        ret += add;
                        c[id] -= add;
                        c[id ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    };
    int res = Dinic(s, t);
    if (res < s1) return {};
    vector<vi> ans(n + 1, vi(n + 1));
    for (int u = 1; u <= n; u++) {
        for (int i : e[u]) {
            int v = to[i] - n, w = c[i ^ 1];
            if (v < 1 || v > n) continue;
            ans[u][v] += w;
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
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
        cout << OUT[!ans.empty()] << "\n";
        int n = (int) ans.size() - 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cout << ans[i][j] << " ";
            cout << "\n";
        }
    }
    return 0;
}
