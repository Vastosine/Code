// Problem : P2770 航空路线问题 https://www.luogu.com.cn/problem/P2770
// Time    : 2026-11-23 14:02:25
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
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
    void solve(int n) {}

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
    int n, m;
    cin >> n >> m;
    map<string, int> mp;
    vector<string> name(n);
    cin >> name;
    for (int i = 0; i < n; i++) mp[name[i]] = i;
    int s = 0, t = 2 * n - 1, N = t + 1;
    MCMF g(N);
    g.addEdge(0, n, 2, 0);
    g.addEdge(n - 1, n * 2 - 1, 2, 0);
    for (int i = 1; i < n - 1; i++) g.addEdge(i, i + n, 1, -1);
    vector<pii> path(m);
    vi pathId(m);
    for (int i = 0; i < m; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        int u = mp[s1], v = mp[s2];
        if (u > v) swap(u, v);
        pathId[i] = g.addEdge(u + n, v, INF, 0);
        path[i] = {u, v};
    }
    auto ret = g.run(s, t);
    if (ret.first < 2) cout << "No Solution!";
    else {
        cout << 2 - ret.second << "\n";
        vector<vi> e(n);
        for (int i = 0; i < m; i++) {
            if (g.flowOn(pathId[i])) {
                auto &[u, v] = path[i];
                e[u].push_back(v);
                e[v].push_back(u);
            }
        }
        vi o(1, 0), vis(n);
        vis[0] = 1;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            cout << name[u] << "\n";
            for (int v : e[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    o.push_back(v);
                    break;
                }
            }
        }
        cout << name[0] << "\n";
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
