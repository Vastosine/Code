#include "Dinic.cpp"

class BoundFlow : private Dinic {
  public:
    // 0-index
    BoundFlow(int n) : Dinic(n + 2), n(n), d(n) {}

    int addEdge(int u, int v, ll l, ll r) {
        int id = Dinic::addEdge(u, v, r - l);
        d[v] += l, d[u] -= l;
        return id;
    }

    pair<bool, ll> feasible() {
        int S = n, T = n + 1;
        ll sum = 0;
        vi e;
        for (int u = 0; u < n; u++) {
            if (d[u] > 0) e.push_back(Dinic::addEdge(S, u, d[u])), sum += d[u];
            if (d[u] < 0) e.push_back(Dinic::addEdge(u, T, -d[u]));
        }
        auto res = Dinic::run(S, T);
        for (int i : e) eraseEdge(i);
        return {res == sum, sum};
    }

    pair<bool, ll> feasible(int s, int t) {
        int e = Dinic::addEdge(t, s, INF);
        auto res = feasible();
        eraseEdge(e);
        return res;
    }

    // mode =  1 : Maximum feasible flow. 
    //
    // mode = -1 : Minimum feasible flow.
    ll run(int s, int t, int mode = 1) {
        auto [res, flow] = feasible(s, t);
        if (!res) return -1;
        return flow + mode * Dinic::run(s, t);
    }

    ll flowOn(int id) const { return Dinic::flowOn(id); }
    void clear(int N = 0) { n = N, d.assign(n, 0), Dinic::clear(n + 2); }
    void resize(int N) { n = N, d.assign(n, 0), Dinic::resize(n + 2); }
    void reassign() { clear(n); }
  private:
    int n;
    vll d;
};

#include <iostream>
using ll = long long;
using vi = vector<int>;
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    BoundFlow a(n + 1);
    vi e(m), L(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll l, r;
        cin >> u >> v >> l >> r;
        L[i] = l;
        e[i] = a.addEdge(u, v, l, r);
    }
    ll ans = 0;a.feasible(s, t);
    if (!~ans) cout << "N";
    else cout << ans << "\n";
    for (int i : e) cout << a.flowOn(i) << " ";

}