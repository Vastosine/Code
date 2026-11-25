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

    bool run() {
        int S = n, T = n + 1;
        ll sum = 0;
        for (int u = 0; u < n; u++) {
            if (d[u] > 0) Dinic::addEdge(S, u, d[u]), sum += d[u];
            if (d[u] < 0) Dinic::addEdge(u, T, -d[u]);
        }
        return Dinic::run(S, T) == sum;
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
    int n, m;
    cin >> n >> m;
    BoundFlow a(n + 1);
    vi e(m), L(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll l, r;
        cin >> u >> v >> l >> r;
        L[i] = l;
        e[i] = a.addEdge(u, v, l, r);
    }
    if (!a.run()) return cout << "No", 0;
    cout << "Yes\n";
    for (int i = 0; i < m; i++) {
        cout << a.flowOn(e[i]) + L[i] << "\n";
    }
}