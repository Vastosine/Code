#include <vector>

using namespace std;

class Dinic {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    static const ll INF = 1ll << 60;
    
    Dinic(int n) : n(n), e(n) {}

    void reassign() { clear(n); }
    void clear(int n = 0) { this->n = n; e.assign(n, {}); to.clear(); cap.clear(); }
    void addEdge(int u, int v, ll c) { add(u, v, c); add(v, u, 0); }

    // Run the Dinic, return the max flow.
    ll run(int s, int t) {
        ll ans = 0;
        while (true) {
            vi cur(n), dep(n), o(1, s);
            dep[s] = 1;
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (int v = to[j]; !dep[v] && cap[j]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
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

    // Print some information or else;
    void print();

  private:
    // Add single edge
    void add(int u, int v, ll c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    int n;
    vector<vi> e;
    vll cap;
    vi to;
};


