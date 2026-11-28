// Problem : P2469 [SDOI2010] 星际竞速 https://www.luogu.com.cn/problem/P2469
// Time    : 2026-11-28 15:51:46
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? " " : "") << a[i]; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<vector<T>> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? "\n" : "") << a[i]; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename T> void Unique(vector<T> &a) { sort(a.begin(), a.end()), a.erase(unique(a.begin(), a.end()), a.end()); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

class MCMF {
  public:
    MCMF(szt n = 0) : n(n), e(n) {}
    
    void clear(szt N = 0) { n = N, e.assign(N, {}), to.clear(), cap.clear(), cost.clear(); }
    void reassign() { clear(n); }
    void resize(szt N) { n = N, e.resize(n); }
    szt addEdge(szt u, szt v, szt c, ll w) { 
        add(u, v, c, w), add(v, u, 0, -w); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the MCMF. run with scale equally when the sign(scale) are equal.
    // i.e. scale = 0 stands for ignoring cost, scale > 0 stands for finding minimum cost, and scale < 0 stands for finding maximum cost.
    // Return {-1, 0} when it has at least one negative cycle reachable from s in the graph
    pair<szt, ll> run(szt s, szt t, ll scale = 1) {
        scale = scale ? scale > 0 ? 1 : -1 : 0;
        ll flow = 0, ans = 0;
        while (true) {
            vst in(n), cnt(n), pre(n, ~0ull);
            vll dis(n, INF);
            queue<szt> q;
            szt ncs;
            auto SPFA = [&] () {
                q.push(s), in[s] = 1, dis[s] = 0;
                while (!q.empty()) {
                    szt u = q.front();
                    q.pop();
                    in[u] = 0;
                    for (szt i : e[u]) {
                        szt v = to[i];
                        ll nd = dis[u] + cost[i] * scale;
                        if (nd < dis[v] && cap[i]) {
                            dis[v] = nd;
                            pre[v] = i;
                            cnt[v] = cnt[u] + 1;
                            if (cnt[v] >= n) return ncs = v, true;
                            if (!in[v]) q.push(v), in[v] = 1;
                        }
                    }
                }
                return false;
            };
            szt lim = INF;
            auto f = [&] (szt v) {
                szt i = pre[v];
                cap[i] -= lim;
                cap[i ^ 1] += lim;
                ans += (ll) lim * cost[i];
                return to[i ^ 1];
            };
            if (SPFA()) return {-1, 0};
            if (!~pre[t]) return {flow, ans};
            for (szt v = t; v != s; v = to[pre[v] ^ 1]) lim = min(lim, cap[pre[v]]);
            for (szt v = t; v != s; v = f(v));
            flow += lim;
        }
    }

    // Print some information or else...
    void solve() {}

    szt flowOn(szt id) const { return cap[id ^ 1]; }

  private:
    void add(szt u, szt v, szt c, ll w) {
        e[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(c);
        cost.push_back(w);
    }

    szt n;
    vector<vst> e;
    vst cap, to;
    vll cost;
};


class BoundCostFlow : public MCMF {
  public:
    // 0-index
    BoundCostFlow(szt n) : MCMF(n + 2), n(n), d(n), baseCost(0) {}

    szt addEdge(szt u, szt v, szt l, szt r, ll w) {
        // cout << u << " " << v << " " << l << " " << r << " " << w << "\n";
        szt id = MCMF::addEdge(u, v, r - l, w);
        d[v] += l, d[u] -= l;
        baseCost += (ll) l * w;
        return id;
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible() {
        szt S = n, T = n + 1;
        szt sum = 0;
        vst e;
        for (szt u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(MCMF::addEdge(S, u, (szt) d[u], 0)), sum += (szt) d[u];
            if (d[u] < 0) e.push_back(MCMF::addEdge(u, T, (szt) -d[u], 0));
        }
        auto res = MCMF::run(S, T);
        res.second += baseCost;
        for (szt i : e) MCMF::eraseEdge(i);
        return pair{res.first == sum, res};
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible(szt s, szt t) {
        szt e = MCMF::addEdge(t, s, INF, 0);
        auto [allow, res] = feasible();
        szt flow = flowOn(e);
        MCMF::eraseEdge(e);
        return {allow, {flow, res.second}};
    }

    szt flowOn(szt id) const { return MCMF::flowOn(id); }
    void clear(szt N = 0) { n = N, d.assign(n, 0), MCMF::clear(n + 2), baseCost = 0; }
    void resize(szt N) { n = N, d.assign(n, 0), MCMF::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    szt n;
  protected:
    vll d;
    ll baseCost;
};

auto Main(int = 0) {
    szt n, m;
    cin >> n >> m;
    szt s = 0, t = n * 2 + 1, N = t + 1;
    BoundCostFlow g(N);
    for (szt i = 1; i <= n; i++) {
        szt x;
        cin >> x;
        g.addEdge(0, i, 0, 1, x);
        g.addEdge(i, i + n, 1, 1, 0);
        g.addEdge(i + n, t, 0, 1, 0);
    }
    while (m--) {
        szt u, v;
        ll w;
        cin >> u >> v >> w;
        if (u > v) swap(u, v);
        g.addEdge(u + n, v, 0, 1, w);
    }
    return g.feasible(s, t).second.second;
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
