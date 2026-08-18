// Problem : P1525 [NOIP 2010 提高组] 关押罪犯 https://www.luogu.com.cn/problem/P1525
// Time    : 2026-08-18 11:26:05

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

struct Edge {
    int u, v, w;
    bool operator<(const Edge &e) {
        return w > e.w;
    }
};

vector<int> f, g;

#define fu (f[get_fa(u)])
#define fv (f[get_fa(v)])
#define gu (g[get_fa(u)])
#define gv (g[get_fa(v)])

int get_fa(int u) {
    if (!f[u]) return u;
    return u == f[u] ? u : f[u] = get_fa(f[u]);
}

int get_g(int u) {
    return g[u] = g[get_fa(u)];
}

void merge(int u, int v) {
    fv = get_fa(u);
    gv = get_g(u);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> e;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({u, v, w});
    }
    std::sort(e.begin(), e.end());
    f.assign(n + 1, 0);
    g.assign(n + 1, 0);
    // for (int i = 1; i <= n; i++) f[i] = i;
    for (const Edge &i : e) {
        int u = i.u, v = i.v, w = i.w;
        if (!fu && !fv) {
            f[u] = u;
            f[v] = v;
            g[u] = v;
            g[v] = u;
        } else {
            if (fu == fv) return cout << w, void();
            if (fu && fv) {
                if (gu == fv) continue;
                int GV = gv;
                merge(gu, fv);
                merge(GV, fu);
            } else {
                if (!fu) merge(gv, u);
                else merge(gu, v);
            }
        }
    }
    cout << 0;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}