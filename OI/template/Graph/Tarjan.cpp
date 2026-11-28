#ifndef __TARJAN__
#define __TARJAN__

#include "../init.cpp"
#include <vector>

using namespace std;

class Tarjan {
  public:
    Tarjan(vector<vst> &e) : n(e.size()), _e(), e(e) {}
    Tarjan(szt n) : n(n), _e(n), e(_e) {}

    void addEdge(szt u, szt v) { e[u].push_back(v); }

    void dfs(szt u) {
        if (dfn[u]) return;
        dfn[u] = low[u] = ++cnt_dfn;
        in[u] = 1;
        st.push_back(u);
        for (szt v : e[u]) {
            if (!dfn[v]) {
                dfs(v);
                Min(low[u], low[v]);
            } else if (in[v]) Min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            szt v;
            do {
                v = st.back();
                st.pop_back();
                scc[v] = cnt_scc;
                in[v] = 0;
            } while (u != v);
            cnt_scc++;
        }
    }

    // returns scc with 0-index
    pair<szt, const vst &> run() {
        assign(n, dfn, low, in);
        scc.assign(n, (szt) -1);
        st.clear();
        cnt_dfn = cnt_scc = 0;
        for (szt i = 0; i < n; i++) dfs(i);
        return {cnt_scc, scc};
    }

    bool inScc(szt u, szt v) const { return scc[u] == scc[v]; }

    vst &operator[] (szt i) { return e[i]; }
    const vst &operator[] (szt i) const { return e[i]; }

    vector<vst> build() {
        if (scc.size() != n) run();
        vector<vst> E(cnt_scc);
        for (szt u = 0; u < n; u++) {
            if (~scc[u]) for (szt v : e[u]) {
                if (!inScc(u, v) && ~scc[v]) E[scc[u]].push_back(scc[v]);
            }
        }
        for (auto &i : E) Unique(i);
        return E;
    }

  private:
    szt n, cnt_dfn, cnt_scc;
    vector<vst> _e, &e;
    vst dfn, scc, low, st;
    vb in;
};

#endif