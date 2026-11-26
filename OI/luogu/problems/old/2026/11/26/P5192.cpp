// Problem : P5192 Shoot the Bullet | 东方文花帖 https://www.luogu.com.cn/problem/P5192
// Time    : 2026-11-26 12:30:42
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(ll x) { return __builtin_popcountll(x); }
void init() {}

class Dinic {
  public:
    // 0-index
    Dinic(szt n) : n(n), e(n) {}

    void resize(szt N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(szt N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    szt addEdge(szt u, szt v, ll c) { add(u, v, c); add(v, u, 0); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the Dinic, return the max flow.
    ll run(szt s, szt t) {
        ll ans = 0;
        while (true) {
            vst cur(n), dep = reachable(s);
            if (!~dep[t]) return ans;
            auto dfs = [&] (auto &&f, szt u, ll lim = INF) {
                if (!lim || u == t) return lim;
                ll ret = 0;
                for (; cur[u] < e[u].size() && ret < lim; cur[u]++) {
                    if (szt i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1 && cap[i]) {
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

    ll flowOn(szt id) const { return cap[id ^ 1]; }

    vst reachable(szt s) const {
        vst o(1, s), dep(n, ~0ull);
        dep[s] = 0;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (szt j : e[u]) {
                if (szt v = to[j]; !~dep[v] && cap[j]) o.push_back(v), dep[v] = dep[u] + 1;
            }
        }
        return dep;
    }

  protected:
    // Add single edge
    void add(szt u, szt v, ll c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    szt n;
    vector<vst> e;
    vll cap;
    vst to;
};

class ISAP : public Dinic {
  public:
    // 0-index
    ISAP(szt n) : Dinic(n) {}

    vst reachable(szt s) const {
        vst o(1, s), dep(n, ~0ull);
        dep[s] = 0;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (szt j : e[u]) {
                if (szt v = to[j]; !~dep[v] && cap[j ^ 1]) o.push_back(v), dep[v] = dep[u] + 1;
            }
        }
        return dep;
    }

    // Run the ISAP, return the max flow.
    ll run(szt s, szt t) {
        ll ans = 0;
        vst cur(n), dep = reachable(t);
        auto dfs = [&] (auto &&f, szt u, szt pre = ~0ull, ll lim = INF) {
            if (!lim || u == t) return lim;
            ll ret = 0;
            for (; cur[u] < e[u].size() && ret < lim; cur[u]++) {
                if (szt i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] - 1 && cap[i]) {
                    ll add = f(f, v, u, min(lim - ret, cap[i]));
                    ret += add;
                    cap[i] -= add;
                    cap[i ^ 1] += add;
                }
            }
            if (ret < lim) {
                dep[u] = n;
                for (szt i : e[u]) {
                    if (szt d = dep[to[i]]; cap[i] && ~d && d + 1 < dep[u]) {
                        dep[u] = d + 1;
                    }
                }
                if (ret && ~pre) dep[u] = min(dep[u], dep[pre] + 1);
                cur[u] = 0;
            }
            return ret;
        };
        while (dep[s] < n) {
            ans += dfs(dfs, s);
        }
        return ans;
    }
};


class HLPP {
  public:
    // 0-index
    HLPP(szt n) : n(n), e(n) {}

    void resize(szt N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(szt N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    szt addEdge(szt u, szt v, szt c) { add(u, v, c); add(v, u, 0); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the HLPP, return the max flow.
    szt run(szt s, szt t) {
        vst dis(n, ~0ull), gap(n * 2);
        auto bfs = [&] () {
            dis[t] = 0;
            vst o(1, t);
            for (szt i = 0; i < o.size(); i++) {
                szt u = o[i];
                gap[dis[u]]++;
                for (szt j : e[u]) {
                    if (szt v = to[j]; !~dis[v] && cap[j ^ 1]) {
                        o.push_back(v), dis[v] = dis[u] + 1;
                    }
                }
            }
        };
        bfs();
        if (!~dis[s]) return 0;
        dis[s] = n;
        vst excess(n), cur(n);
        vb active(n);
        vector<vst> bucket(n * 2);
        excess[s] = INF;
        szt h = 0;
        auto activate = [&] (szt u) { 
            if (!active[u] && u != s && u != t) {
                active[u] = true; 
                bucket[dis[u]].push_back(u);
                h = max(h, dis[u]);
            }
        };
        // Return weather u has excess.
        auto push = [&] (szt u) {
            for (; cur[u] < e[u].size(); cur[u]++) {
                if (szt i = e[u][cur[u]], v = to[i]; ~dis[v] && dis[v] < dis[u] && cap[i]) {
                    szt stream = min(excess[u], cap[i]);
                    if (v != s) excess[v] += stream;
                    if (u != s) excess[u] -= stream;
                    cap[i] -= stream;
                    cap[i ^ 1] += stream;
                    activate(v);
                    if (!excess[u]) return false;
                }
            }
            return true;
        };
        push(s);
        while (true) {
            while (h && bucket[h].empty()) h--;
            if (!h) break;
            szt u = bucket[h].back();
            active[u] = false;
            bucket[h].pop_back();
            while (push(u)) {
                szt d = dis[u];
                cur[u] = 0;
                if (gap[d] == 1) {
                    for (szt i = 0; i < n; i++) {
                        if (dis[i] < n && dis[i] >= d) {
                            gap[dis[i]]--;
                            dis[i] = n + 1;
                            gap[dis[i]]++;
                            cur[i] = 0;
                        }
                    }
                } else {
                    gap[d]--;
                    d = 2 * n - 1;
                    for (szt i : e[u]) {
                        if (szt v = to[i]; cap[i] && u != v && ~dis[v]) {
                            d = min(d, dis[v] + 1);
                        }
                    }
                    gap[d]++;
                    dis[u] = d;
                }
                
            }
        }
        return excess[t];
    }

    szt flowOn(szt id) const { return cap[id ^ 1]; }

  protected:
    // Add single edge
    void add(szt u, szt v, szt c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    szt n;
    vector<vst> e;
    vst cap;
    vst to;
};

template<typename Dinic = Dinic>
class BoundFlow : private Dinic {
  public:
    // 0-index
    BoundFlow(size_t n) : Dinic(n + 2), n(n), d(n) {}

    size_t addEdge(size_t u, size_t v, ll l, ll r) {
        size_t id = Dinic::addEdge(u, v, r - l);
        d[v] += l, d[u] -= l;
        return id;
    }

    pair<bool, ll> feasible() {
        size_t S = n, T = n + 1;
        ll sum = 0;
        vst e;
        for (size_t u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(Dinic::addEdge(S, u, d[u])), sum += d[u];
            if (d[u] < 0) e.push_back(Dinic::addEdge(u, T, -d[u]));
        }
        auto res = Dinic::run(S, T);
        for (size_t i : e) Dinic::eraseEdge(i);
        return {res == sum, sum};
    }

    pair<bool, ll> feasible(size_t s, size_t t) {
        size_t e = Dinic::addEdge(t, s, INF);
        bool allow = feasible().first;
        ll flow = flowOn(e);
        Dinic::eraseEdge(e);
        return {allow, flow};
    }

    // mode = 0 : Maximum feasible flow. 
    //
    // mode = 1 : Minimum feasible flow.
    ll run(size_t s, size_t t, bool mode = 0) {
        auto [res, flow] = feasible(s, t);
        if (!res) return -1;
        return flow + (mode ? -Dinic::run(t, s) : Dinic::run(s, t));
    }

    ll flowOn(size_t id) const { return Dinic::flowOn(id); }
    void clear(size_t N = 0) { n = N, d.assign(n, 0), Dinic::clear(n + 2); }
    void resize(size_t N) { n = N, d.assign(n, 0), Dinic::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    size_t n;
    vll d;
};

auto Main([[maybe_unused]] int C = 0) {
    szt n, m;
    if (!(cin >> n >> m)) return -2ll;
    szt s = 0, t = n + m + 1, N = t + 1;
    BoundFlow<HLPP> g(N);
    for (szt i = 1; i <= m; i++) {
        ll x;
        cin >> x;
        g.addEdge(i + n, t, x, INF);
    }
    for (szt i = 1; i <= n; i++) {
        szt c;
        ll d;
        cin >> c >> d;
        g.addEdge(s, i, 0, d);
        vll L(m + 1), R(m + 1);
        while (c--) {
            ll l, r;
            szt v;
            cin >> v >> l >> r;
            L[v + 1] += l;
            R[v + 1] += r;
        }
        for (szt j = 1; j <= m; j++) {
            if (R[j]) g.addEdge(i, j + n, L[j], R[j]);
        }
    }
    return g.run(s, t);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    while (true) {
        [[maybe_unused]] auto ans = Main();
        if (ans == -2) return 0;
        cout << ans << "\n\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
