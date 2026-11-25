#include <vector>

using namespace std;

class Dinic {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    static constexpr ll INF = 1ll << 60;
    
    // 0-index
    Dinic(int n) : n(n), e(n) {}

    void resize(int N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(int N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    int addEdge(int u, int v, ll c) { add(u, v, c); add(v, u, 0); return (int) to.size() - 2; }
    void eraseEdge(int id) { cap[id] = cap[id ^ 1] = 0; }

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
