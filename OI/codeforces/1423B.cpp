// Problem : B. Valuable Paper https://codeforces.com/problemset/problem/1423/B
// Time    : 2026-11-12 07:54:00
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

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    int s = 0, t = 2 * n + 1, N = 2 * n + 2;
    vector<vi> e, E(m, vi(3));
    vi to, c, dep, cur, _c;
    assign(N, e);
    for (auto &i : E) {
        cin >> i[1] >> i[2] >> i[0];
    }
    Sort(E);
    auto addEdge = [&] (int u, int v, int w = 1) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    for (int u = 1; u <= n; u++) {
        addEdge(s, u);
        addEdge(u + n, t);
    }
    for (auto &i : E) {
        addEdge(i[1], i[2] + n);
    }
    auto Dinic = [&] (int s, int t, int restrict) {
        int ans = 0;
        auto visible = [&] (int x) {
            return x / 2 <= restrict;
        };
        while (true) {
            assign(N, dep, cur);
            dep[s] = 1;
            vi o(1, s);
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (!visible(j)) break;
                    int v = to[j];
                    if (c[j] && !dep[v]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, int lim = inf) {
                if (!lim || u == t) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    int id = e[u][cur[u]], v = to[id], w = c[id];
                    if (visible(id) && dep[v] == dep[u] + 1) {
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
    _c = c;
    if (Dinic(s, t, 1 << 25) < n) return -1;
    int l = 2 * n - 1, r = 2 * n + m + 1;
    while (l < r - 1) {
        int x = ((l + r) >> 1);
        c = _c;
        int d = Dinic(s, t, x);
        if (d == n) r = x;
        else l = x;
    }
    return E[r - 2 * n][0];
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
