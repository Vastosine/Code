#ifndef __ISAP__
#define __ISAP__
#include "../init.cpp"
#include "Dinic.cpp"

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
    szt run(szt s, szt t) {
        szt ans = 0;
        vst cur(n), dep = reachable(t), gap(n + 1);
        for (szt x : dep) if (~x) gap[x]++;
        auto dfs = [&] (auto &&f, szt u, szt pre = ~0ull, szt lim = INF) {
            if (!lim || u == t) return lim;
            szt ret = 0;
            for (; cur[u] < e[u].size() && ret < lim; cur[u]++) {
                if (szt i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] - 1 && cap[i]) {
                    szt add = f(f, v, u, min(lim - ret, cap[i]));
                    ret += add;
                    cap[i] -= add;
                    cap[i ^ 1] += add;
                }
            }
            if (ret < lim) {
                if (!--gap[dep[u]]) return gap[u] = n, ret;
                dep[u] = n;
                for (szt i : e[u]) {
                    if (szt d = dep[to[i]]; cap[i] && ~d && d + 1 < dep[u]) {
                        dep[u] = d + 1;
                    }
                }
                if (ret && ~pre) dep[u] = min(dep[u], dep[pre] + 1);
                cur[u] = 0;
                gap[dep[u]]++;
            }
            return ret;
        };
        while (dep[s] < n) {
            ans += dfs(dfs, s);
        }
        return ans;
    }
};

#endif

