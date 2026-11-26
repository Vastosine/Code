// Problem : P4043 [AHOI2014/JSOI2014] 支线剧情 https://www.luogu.com.cn/problem/P4043
// Time    : 2026-11-26 09:05:50
#ifndef __BOUND_COST_FLOW__
#define __BOUND_COST_FLOW__

#ifndef __MCMF__
#define __MCMF__
#ifndef __INIT__
#define __INIT__

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std; 

typedef long long ll; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
typedef vector<ll> vll; 
typedef pair<ll, ll> pll;
typedef unsigned long long szt;
typedef vector<szt> vst;
typedef pair<szt, szt> pst;

[[maybe_unused]] const ll INF = 1ll << 60; 
[[maybe_unused]] const int inf = 0x3fffffff;

template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

#endif
#include <queue>

class MCMF {
  public:
    MCMF(szt n = 0) : n(n), e(n) {}
    
    void clear(szt N = 0) { n = N, e.assign(N, {}), to.clear(), cap.clear(), cost.clear(); }
    void reassign() { clear(n); }
    void resize(szt N) { n = N, e.resize(n); }
    szt addEdge(szt u, szt v, ll c, ll w) { add(u, v, c, w), add(v, u, 0, -w); return (szt) to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the MCMF. run with scale equally when the sign(scale) are equal.
    // i.e. scale = 0 stands for ignoring cost, scale > 0 stands for finding minimum cost, and scale < 0 stands for finding maximum cost.
    // Return {-1, 0} when it has at least one negative cycle in the graph
    pll run(szt s, szt t, ll scale = 1) {
        scale = scale ? scale > 0 ? 1 : -1 : 0;
        ll flow = 0, ans = 0;
        while (true) {
            vst in(n), cnt(n), pre(n, ~0ull);
            vll dis(n, INF);
            queue<szt> q;
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
                        if (cnt[v] >= n) return {-1, 0};
                        if (!in[v]) q.push(v), in[v] = 1;
                    }
                }
            }
            if (!~pre[t]) return {flow, ans};
            ll lim = INF;
            for (szt v = t; v != s; v = to[pre[v] ^ 1]) lim = min(lim, cap[pre[v]]);
            for (szt v = t; v != s; ) {
                szt i = pre[v];
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

    ll flowOn(szt id) const { return cap[id ^ 1]; }

  private:
    void add(szt u, szt v, ll c, ll w) {
        e[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(c);
        cost.push_back(w);
    }

    szt n;
    vector<vst> e;
    vst to;
    vll cap, cost;
};

#endif

class BoundCostFlow : private MCMF {
  public:
    // 0-index
    BoundCostFlow(size_t n) : MCMF(n + 2), n(n), d(n), baseCost(0) {}

    size_t addEdge(size_t u, size_t v, ll l, ll r, ll w) {
        size_t id = MCMF::addEdge(u, v, r - l, w);
        d[v] += l, d[u] -= l;
        baseCost += l * w;
        return id;
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible() {
        size_t S = n, T = n + 1;
        ll sum = 0;
        vst e;
        for (size_t u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(MCMF::addEdge(S, u, d[u], 0)), sum += d[u];
            if (d[u] < 0) e.push_back(MCMF::addEdge(u, T, -d[u], 0));
        }
        auto res = MCMF::run(S, T);
        res.second += baseCost;
        for (size_t i : e) MCMF::eraseEdge(i);
        return pair{res.first == sum, res};
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible(size_t s, size_t t) {
        size_t e = MCMF::addEdge(t, s, INF, 0);
        auto [allow, res] = feasible();
        ll flow = flowOn(e);
        MCMF::eraseEdge(e);
        return {allow, {flow, res.second}};
    }

    // mode = 0 : Maximum feasible flow. 
    //
    // mode = 1 : Minimum feasible flow.
    // pll run(size_t s, size_t t, bool mode = 0) {
    //     auto [allow, res] = feasible(s, t);
    //     if (!allow) return {-1, -1};
    //     if (mode) {
    //         auto ans = MCMF::run(t, s);
    //         return {res.first - ans.first, res.second - ans.second};
    //     } else {
    //         auto ans = MCMF::run(s, t);
    //         return {res.first + ans.first, res.second + ans.second};
    //     }
    // }

    ll flowOn(size_t id) const { return MCMF::flowOn(id); }
    void clear(size_t N = 0) { n = N, d.assign(n, 0), MCMF::clear(n + 2), baseCost = 0; }
    void resize(size_t N) { n = N, d.assign(n, 0), MCMF::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    size_t n;
    vll d;
    ll baseCost;
};

#endif


int main() {
    szt n;
    cin >> n;
    BoundCostFlow a(n + 1);
    for (szt u = 1; u <= n; u++) {
        szt k;
        cin >> k;
        a.addEdge(u, 0, 0, INF, 0);
        while (k--) {
            szt v;
            ll w;
            cin >> v >> w;
            a.addEdge(u, v, 1, INF, w);
        }
    }
    cout << a.feasible(1, 0).second.second;
}
