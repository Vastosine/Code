// Problem : P3254 圆桌问题 https://www.luogu.com.cn/problem/P3254
// Time    : 2026-11-12 18:32:29
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
    vector<vi> e;
    vi to, dep, cur;
    vll c;
    int N = n + m + 2, s = 0, t = N - 1, sum = 0;
    auto addEdge = [&] (int u, int v, ll w) {
        e[u].push_back(to.size());
        to.push_back(v);;
        c.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
    };
    assign(N, e);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        addEdge(0, i, x);
        sum += x;
    }
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        addEdge(n + i, t, x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            addEdge(i, j + n, 1);
        }
    }
    auto Dinic = [&] (int s, int t) {
        ll ans = 0;
        while (true) {
            assign(N, dep, cur);
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
            auto dfs = [&] (auto &&f, int u, ll lim = INF) {
                if (!lim || u == t) return lim;
                ll ret = 0;
                for (; cur[u] < (int) e[u].size(); cur[u]++) {
                    int id = e[u][cur[u]], v = to[id];
                    if (dep[v] == dep[u] + 1) {
                        int add = f(f, v, min(c[id], lim - ret));
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
    if (Dinic(s, t) < sum) return cout << 0, 0;
    cout << "1\n";
    for (int u = 1; u <= n; u++) {
        for (int i : e[u]) {
            if (c[i ^ 1]) cout << to[i] - n << " ";
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
