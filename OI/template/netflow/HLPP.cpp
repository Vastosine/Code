#ifndef __HLPP__
#define __HLPP__
#include "../init.cpp"

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
        while (h) {
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
            while (h && bucket[h].empty()) h--;
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

#endif