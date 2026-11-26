#ifndef __DINIC__
#define __DINIC__
#include "../init.cpp"

class Dinic {
  public:
    // 0-index
    Dinic(szt n) : n(n), e(n) {}

    void resize(szt N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(szt N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    szt addEdge(szt u, szt v, szt c) { add(u, v, c); add(v, u, 0); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the Dinic, return the max flow.
    szt run(szt s, szt t) {
        szt ans = 0;
        while (true) {
            vst cur(n), dep = reachable(s);
            if (!~dep[t]) return ans;
            auto dfs = [&] (auto &&f, szt u, szt lim = INF) {
                if (!lim || u == t) return lim;
                szt ret = 0;
                for (; cur[u] < e[u].size() && ret < lim; cur[u]++) {
                    if (szt i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1 && cap[i]) {
                        szt add = f(f, v, min(lim - ret, cap[i]));
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

    szt flowOn(szt id) const { return cap[id ^ 1]; }

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
    void add(szt u, szt v, szt c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    szt n;
    vector<vst> e;
    vst cap, to;
};

#endif