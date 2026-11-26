// Problem : P3980 [NOI2008] 志愿者招募 https://www.luogu.com.cn/problem/P3980
// Time    : 2026-11-26 11:47:27
#ifndef __INIT__
#define __INIT__

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std; 

typedef long long ll; 
typedef vector<bool> vb; 
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
    szt addEdge(szt u, szt v, ll c, ll w) { add(u, v, c, w), add(v, u, 0, -w); return to.size() - 2; }
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
            ll lim = INF;
            auto f = [&] (szt v) {
                szt i = pre[v];
                cap[i] -= lim;
                cap[i ^ 1] += lim;
                ans += lim * cost[i];
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

int main() {
    szt n, m;
    cin >> n >> m;
    vll a(n);
    cin >> a;
    ll mx = *max_element(a.begin(), a.end());
    szt s = 0, t = n + 1, N = t + 1;
    MCMF g(N);
    g.addEdge(s, 1, mx, 0);
    for (szt i = 1; i <= n; i++) {
        g.addEdge(i, i + 1, mx - a[i - 1], 0);
        g.addEdge(i + 1, i, INF, 0);
    }
    while (m--) {
        szt u, v;
        ll w;
        cin >> u >> v >> w;
        g.addEdge(u, v + 1, INF, w);
    }
    cout << g.run(s, t).second;
}