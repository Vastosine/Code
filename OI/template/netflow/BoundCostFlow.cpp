#ifndef __BOUND_COST_FLOW__
#define __BOUND_COST_FLOW__

#include "MCMF.cpp"
#include <cassert>

class BoundCostFlow : protected MCMF {
  public:
    // 0-index
    BoundCostFlow(szt n) : MCMF(n + 2), n(n), d(n), baseCost(0) {}

    szt addEdge(szt u, szt v, ll l, ll r, ll w) {
        szt id = MCMF::addEdge(u, v, r - l, w);
        d[v] += l, d[u] -= l;
        baseCost += l * w;
        return id;
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible() {
        szt S = n, T = n + 1;
        ll sum = 0;
        vst e;
        for (szt u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(MCMF::addEdge(S, u, d[u], 0)), sum += d[u];
            if (d[u] < 0) e.push_back(MCMF::addEdge(u, T, -d[u], 0));
        }
        auto res = MCMF::run(S, T);
        res.second += baseCost;
        for (szt i : e) MCMF::eraseEdge(i);
        return pair{res.first == sum, res};
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible(szt s, szt t) {
        szt e = MCMF::addEdge(t, s, INF, 0);
        auto [allow, res] = feasible();
        ll flow = flowOn(e);
        MCMF::eraseEdge(e);
        return {allow, {flow, res.second}};
    }

    ll flowOn(szt id) const { return MCMF::flowOn(id); }
    void clear(szt N = 0) { n = N, d.assign(n, 0), MCMF::clear(n + 2), baseCost = 0; }
    void resize(szt N) { n = N, d.assign(n, 0), MCMF::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    szt n;
  protected:
    vll d;
    ll baseCost;
};

class NegMCMF : private BoundCostFlow {
  public:
    NegMCMF(szt n) : BoundCostFlow(n) {}

    szt addEdge(szt u, szt v, ll c, ll w) {
        if (w >= 0) return BoundCostFlow::addEdge(u, v, 0, c, w);
        szt id = 1 ^ MCMF::addEdge(v, u, c, -w);
        d[v] += c, d[u] -= c;
        baseCost += c * w;
        return id;
    }

    // {flow, cost}
    pll run(szt s, szt t) {
        auto [allow, res] = feasible();
        assert(allow);
        auto [f1, c1] = res;
        auto [f2, c2] = MCMF::run(s, t);
        return {f2, c1 + c2};
    }
};

#endif
