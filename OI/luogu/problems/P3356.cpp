// Problem : P3356 火星探险问题 https://www.luogu.com.cn/problem/P3356
// Time    : 2026-11-23 15:07:30
#include <algorithm>
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

auto Main([[maybe_unused]] int C = 0) {
    int n, r, c;
    cin >> n >> c >> r;
    vector<vi> a(r, vi(c));
    vector<vector<vi>> e(r, vector<vi>(c, vi(2, -1))), fl(r, vector<vi>(c, vi(2, 0)));
    cin >> a;
    auto f = [&] (int x, int y, int z) {
        return (z * r + x) * c + y;
    };
    int s = 0, t = r * c * 2, N = t + 1;
    MCMF g(N);
    g.addEdge(t - 1, t, n, 0);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int u = f(i, j, 0), v = f(i, j, 1);
            if (a[i][j] != 1) g.addEdge(u, v, INF, 0);
            if (a[i][j] == 2) g.addEdge(u, v, 1, -1);
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int u = f(i, j, 1), v = f(i, j + 1, 0), w = f(i + 1, j, 0);
            if (i < r - 1) e[i][j][0] = g.addEdge(u, w, INF, 0);
            if (j < c - 1) e[i][j][1] = g.addEdge(u, v, INF, 0);
        }
    }
    g.run(s, t);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < 2; k++) {
                if (~e[i][j][k]) fl[i][j][k] = g.flowOn(e[i][j][k]);
            }
        }
    }
    vector<pii> cur(n);
    while (cur[0] != pii{r - 1, c - 1}) {
        for (int i = 0; i < n; i++) {
            auto &[u, v] = cur[i];
            for (int k = 0; k < 2; k++) {
                if (fl[u][v][k]) {
                    cout << i + 1 << " " << k << "\n";
                    fl[u][v][k]--;
                    u += !k;
                    v += k;
                    break;
                }
            }
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
