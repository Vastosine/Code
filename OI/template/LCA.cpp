#include <vector>

using namespace std;

using vi = vector<int>;

// e is given by main
vector<vi> e, f;
int n;
vi dep;
int D;

void init() {
    D = __lg(n) + 1;
    f.assign(n + 1, vi(D + 1));
    dep.assign(n + 1, 0);
    vi o(1, 1);
    dep[1] = 1;
    f[1][0] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v), f[v][0] = u;
        }
    }
    for (int d = 0; d < D; d++) {
        for (int u = 1; u <= n; u++) {
            f[u][d + 1] = f[f[u][d]][d];
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int d = D; ~d; d--) {
        int nu = f[u][d];
        if (dep[nu] >= dep[v]) u = nu;
    }
    if (u == v) return u;
    for (int d = D; ~d; d--) {
        int nu = f[u][d], nv = f[v][d];
        if (nu != nv) u = nu, v = nv;
    }
    return f[u][0];
}

int dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
}

int kfa(int u, int k) {
    if (k < 0) return u;
    int d = 0;
    while (k) {
        if (k & 1) u = f[u][d];
        d++;
        k /= 2;
    }
    return u;
}