#ifndef __BOUND_COST_FLOW__
#define __BOUND_COST_FLOW__

#include "MCMF.cpp"

class BoundCostFlow : private MCMF {
  public:
    // 0-index
    BoundCostFlow(size_t n) : MCMF(n + 2), n(n), d(n), baseCost(0) {}

    size_t addEdge(size_t u, size_t v, ll l, ll r, ll w) {
        size_t id = MCMF::addEdge(u, v, r - l, w);
        d[v] += l, d[u] -= l;
        baseCost += l * w;
        return id;
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible() {
        size_t S = n, T = n + 1;
        ll sum = 0;
        vst e;
        for (size_t u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(MCMF::addEdge(S, u, d[u], 0)), sum += d[u];
            if (d[u] < 0) e.push_back(MCMF::addEdge(u, T, -d[u], 0));
        }
        auto res = MCMF::run(S, T);
        res.second += baseCost;
        for (size_t i : e) MCMF::eraseEdge(i);
        return pair{res.first == sum, res};
    }

    // {allow, {flow, cost}}
    pair<bool, pll> feasible(size_t s, size_t t) {
        size_t e = MCMF::addEdge(t, s, INF, 0);
        auto [allow, res] = feasible();
        ll flow = flowOn(e);
        MCMF::eraseEdge(e);
        return {allow, {flow, res.second}};
    }

    // mode = 0 : Maximum feasible flow. 
    //
    // mode = 1 : Minimum feasible flow.
    // pll run(size_t s, size_t t, bool mode = 0) {
    //     auto [allow, res] = feasible(s, t);
    //     if (!allow) return {-1, -1};
    //     if (mode) {
    //         auto ans = MCMF::run(t, s);
    //         return {res.first - ans.first, res.second - ans.second};
    //     } else {
    //         auto ans = MCMF::run(s, t);
    //         return {res.first + ans.first, res.second + ans.second};
    //     }
    // }

    ll flowOn(size_t id) const { return MCMF::flowOn(id); }
    void clear(size_t N = 0) { n = N, d.assign(n, 0), MCMF::clear(n + 2), baseCost = 0; }
    void resize(size_t N) { n = N, d.assign(n, 0), MCMF::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    size_t n;
    vll d;
    ll baseCost;
};

#endif
