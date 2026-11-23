// Problem : P2766 最长不下降子序列问题 https://www.luogu.com.cn/problem/P2766
// Time    : 2026-11-23 09:03:38
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}


class Dinic {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    static constexpr ll INF = 1ll << 60;
    
    Dinic(int n) : n(n), e(n) {}

    void reassign() { clear(n); }
    void clear(int N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    int addEdge(int u, int v, ll c) { add(u, v, c); add(v, u, 0); return (int) to.size() - 2; }

    // Run the Dinic, return the max flow.
    ll run(int s, int t) {
        ll ans = 0;
        while (true) {
            vi cur(n), dep = reachable(s);
            if (!~dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, ll lim = INF) {
                if (!lim || u == t) return lim;
                ll ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    if (int i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1 && cap[i]) {
                        ll add = f(f, v, min(lim - ret, cap[i]));
                        ret += add;
                        cap[i] -= add;
                        cap[i ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    }

    ll flowOn(int id) const { return cap[id ^ 1]; }

    vi reachable(int s) const {
        vi o(1, s), dep(n, -1);
        dep[s] = 0;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j : e[u]) {
                if (int v = to[j]; !~dep[v] && cap[j]) o.push_back(v), dep[v] = dep[u] + 1;
            }
        }
        return dep;
    }

  private:
    // Add single edge
    void add(int u, int v, ll c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    int n;
    vector<vi> e;
    vll cap;
    vi to;
};


auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n + 1), f(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 0; j < i; j++) {
            if (a[i] >= a[j]) f[i] = max(f[i], f[j] + 1);
        }
        ans = max(ans, f[i]);
    }
    cout << ans << "\n";
    int s = 0, t = 2 * n + 1, N = t + 1;
    Dinic d(N);
    auto ass = [&] (int mode) {
        d.reassign();
        for (int i = 1; i <= n; i++) {
            if (f[i] == 1) d.addEdge(s, i, i == 1 && mode ? INF : 1);
            if (f[i] == ans) d.addEdge(i + n, t, i == n && mode ? INF : 1);
            d.addEdge(i, i + n, mode && (i == 1 || i == n) ? INF : 1);
            for (int j = 1; j < i; j++) {
                if (a[j] <= a[i] && f[j] + 1 == f[i]) d.addEdge(j + n, i, 1);
            }
        }
    };
    ass(0);
    cout << d.run(s, t) << "\n";
    ass(1);
    if (ans == 1) cout << n;
    else cout << d.run(s, t) << "\n";
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
