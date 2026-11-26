#ifndef __BOUND_FLOW__
#define __BOUND_FLOW__

#include "Dinic.cpp"

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

#endif
