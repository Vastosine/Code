// Problem : B. Valuable Paper https://codeforces.com/problemset/problem/1423/B
// Time    : 2026-11-13 08:52:58
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
    cin >> n >> m;
    vector<vll> E(m, vll(3));
    for (auto &i : E) cin >> i[1] >> i[2] >> i[0];
    Sort(E);
    int s = 0, t = 2 * n + 1, N = t + 1;
    vector<vi> e(N);
    vi to, dep, cur;
    vll c;
    auto addEdge = [&] (int u, int v, ll w) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, 1);
        addEdge(i + n, t, 1);
    }
    for (auto &i : E) {
        addEdge(i[1], i[2] + n, 1);
    }
    auto Dinic = [&] (int s, int t, int re) {
        auto visible = [&] (int x) {
            return x / 2 <= re;
        };
        ll ans = 0;
        while (true) {
            assign(N, dep, cur);
            dep[s] = 1;
            vi o(1, s);
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (int v = to[j]; !dep[v] && c[j] && visible(j)){
                        dep[v] = dep[u] + 1, o.push_back(v);
                    }
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, ll lim = INF) {
                if (!lim || u == t) return lim;
                ll ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    if (int i = e[u][cur[u]]; visible(i) && dep[to[i]] == dep[u] + 1) {
                        ll add = f(f, to[i], min(lim - ret, c[i]));
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
    vll _c = c;
    if (Dinic(s, t, 1 << 30) < n) return -1ll;
    int l = -1, r = m + 1;
    while (l < r - 1) {
        int x = (l + r) >> 1;
        c = _c;
        ll y = Dinic(s, t, n * 2 + x);
        if (y == n) r = x;
        else l = x;
    }
    return E[r][0];
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
