// Problem : P3357 最长 k 可重线段集问题 https://www.luogu.com.cn/problem/P3357
// Time    : 2026-11-23 15:36:14
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
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

class MCMF {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    using pll = pair<ll, ll>;
    static constexpr ll INF = 1ll << 60;
    
    MCMF(int n = 0) : n(n), e(n) {}
    void clear(int N = 0) { n = N, e.assign(N, {}), to.clear(), cap.clear(), cost.clear(); }
    void reassign() { clear(n); }

    int addEdge(int u, int v, ll c, ll w) { add(u, v, c, w), add(v, u, 0, -w); return (int) to.size() - 2; }

    // Run the MCMF. run with scale equally when the sign(scale) are equal.
    // i.e. scale = 0 stands for ignoring cost, scale > 0 stands for finding minimum cost, and scale < 0 stands for finding maximum cost.
    // Return {-1, 0} when it has at least one negative cycle in the graph
    pll run(int s, int t, ll scale = 1) {
        scale = scale ? scale > 0 ? 1 : -1 : 0;
        ll flow = 0, ans = 0;
        while (true) {
            vi in(n), cnt(n), pre(n, -1);
            vll dis(n, INF);
            queue<int> q;
            q.push(s), in[s] = 1, dis[s] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in[u] = 0;
                for (int i : e[u]) {
                    int v = to[i];
                    ll nd = dis[u] + cost[i] * scale;
                    if (nd < dis[v] && cap[i]) {
                        dis[v] = nd;
                        pre[v] = i;
                        cnt[v] = cnt[u] + 1;
                        if (cnt[v] >= n) return {-1, 0};
                        if (!in[v]) q.push(v), in[v] = 1;

                    }
                }
            }
            if (!~pre[t]) return {flow, ans};
            ll lim = INF;
            for (int v = t; v != s; v = to[pre[v] ^ 1]) lim = min(lim, cap[pre[v]]);
            for (int v = t; v != s; ) {
                int i = pre[v];
                cap[i] -= lim;
                cap[i ^ 1] += lim;
                ans += lim * cost[i];
                v = to[i ^ 1];
            }
            flow += lim;
        }
    }

    // Print some information or else...
    void solve() {}

    ll flowOn(int id) const { return cap[id ^ 1]; }

  private:
    void add(int u, int v, ll c, ll w) {
        e[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(c);
        cost.push_back(w);
    }

    int n;
    vector<vi> e;
    vi to;
    vll cap, cost;
};

ll sqr(ll x) { return x * x; }
ll dis(ll x1, ll y1, ll x2, ll y2) { return sqrt(sqr(x1 - x2) + sqr(y1 - y2)); }

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    vector<vll> a(n, vll(4));
    cin >> a;
    vll p, d(n);
    auto f = [&] (ll x) { return lower_bound(p.begin(), p.end(), x) - p.begin(); };
    for (int i = 0; i < n; i++) {
        p.push_back(a[i][0]);
        p.push_back(a[i][2]);
        if (a[i][0] > a[i][2]) swap(a[i][0], a[i][2]);
        d[i] = dis(a[i][0], a[i][1], a[i][2], a[i][3]);
    }
    Sort(p);
    p.erase(unique(p.begin(), p.end()), p.end());
    int m = (int) p.size(), s = 0, t = m * 2, N = t + 1;
    MCMF g(N);
    g.addEdge(t - 1, t, k, 0);
    for (int i = 0; i < m; i++) g.addEdge(i, i + m, INF, 0);
    for (int i = 1; i < m; i++) g.addEdge(i - 1 + m, i, INF, 0);
    for (int i = 0; i < n; i++) {
        int u = f(a[i][0]), v = f(a[i][2]);
        if (u == v) g.addEdge(u, u + m, 1, -d[i]);
        else g.addEdge(u + m, v, 1, -d[i]);
    }
    return -g.run(s, t).second;
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
