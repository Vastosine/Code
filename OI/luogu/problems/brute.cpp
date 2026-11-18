// Problem : P17805 [ICPC 2019 Nanchang R] A Funny Bipartite Graph https://www.luogu.com.cn/problem/P17805
// Time    : 2026-11-18 09:28:50
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = (ll)1 << 60; [[maybe_unused]] const int inf = 0x3fffffff;
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
    int n;
    cin >> n;
    vector<string> e(n), t(n);
    vector<vi> w(n, vi(3)), re(n);
    cin >> e >> t;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        w[i][0] = x;
        for (int j = 0; j < 2; j++) {
            w[i][j + 1] = w[i][j] * x;
        }
        for (int j = 2; j; j--) w[i][j] -= w[i][j - 1];

        for (int j = 0; j < n; j++) {
            if (t[i][j] == '1') re[i].push_back(j);
        }
        // if (!re[i].empty()) no |= (1 << i);
    }
    vi vis(1 << n);
    auto check = [&] (int id) {
        if (vis[id]) return false;
        // if ((id & no) != id) return false;
        for (int i = 0; i < n; i++) {
            for (int j : re[i]) {
                if ((id & (1 << i)) && (id & (1 << j))) return false;
            }
        }
        return true;
    };
    ll ans = INF;
    for (int mask = (1 << n) - 1; mask > 0; mask -= 2) {
        if (!check(mask)) continue;
        // if (!vis[mask]) for (int i = mask; i; i = (i - 1) & mask) {
        //     vis[i] = 1;
        // }
        int S = n * 2, T = S + 1, N = T + 1;
        MCMF a(N);
        for (int i = 0; i < n; i++) {
            a.addEdge(i + n, T, 1, 0);
            if ((1 << i) & mask) {
                for (int j = 0; j < 3; j++) {
                    a.addEdge(S, i, 1, w[i][j]);
                }
                for (int j = 0; j < n; j++) {
                    if (e[i][j] == '1') {
                        a.addEdge(i, j + n, 1, 0);
                    } 
                }
            }
        }
        auto [u, v] = a.run(S, T);
        if (u == n) ans = min(ans, v);
    }
    return ans == INF ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
