#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Reroot {
  public:
    using vi = vector<int>;

    Reroot(int n, bool needS = false) : n(n), e(n + 1), needS(needS) {}

    void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
    
    friend istream &operator>>(istream &in, Reroot &tree) {
        for (int i = 1; i < tree.n; i++) {
            int u, v;
            in >> u >> v;
            tree.addEdge(u, v);
        }
        tree.build();
        return in;
    }

    void build(int rt = 1) {
        root = rt;
        if (needS) {
            s.assign(n + 1, {});
            for (int u = 0; u <= n; u++) s[u].reserve(e[u].size());
        }
        fa.assign(n + 1, -1);
        dep.assign(n + 1, 0);
        o.assign(1, root);
        fa[root] = root;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int v : e[u]) {
                if (!~fa[v]) {
                    fa[v] = u;
                    if (needS) s[u].push_back(v);
                    dep[v] = dep[u] + 1;
                    o.push_back(v);
                }
            }
        }
        assert((int) o.size() == n);
        ro = o;
        reverse(ro.begin(), ro.end());
    }

    bool isLeaf(int u) { return e[u].size() == 1 && u != root; }

    const vi &downOrder() { return check(), o; }
    const vi &upOrder() { return check(), ro; }

    int &operator[](int i) { return fa[i]; }
    const int &operator[](int i) const { return fa[i]; }
    
  private:
    void check() { if (o.empty()) build(); }

    int n, root;
    vector<vi> e, s;
    vi fa, dep, o, ro, siz;
    bool needS;
};

using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;

void P3478() {
    int n;
    cin >> n;
    Reroot t(n);
    cin >> t;
    vll f(n + 1), res(n + 1);
    vi siz(n + 1);
    for (int u : t.upOrder()) {
        siz[u] += 1;
        if (u != 1) {
            int fa = t[u];
            siz[fa] += siz[u];
            f[fa] += f[u] + siz[u];
        }
    } 
    for (int u : t.downOrder()) {
        if (u == 1) res[u] = f[u];
        else {
            ll add = res[t[u]] - f[u] - siz[u] + n - siz[u];
            res[u] = f[u] + add;
        }
    }
    // for (int i = 1; i <= n; i++) cout << res[i] << " ";
    cout << max_element(res.begin() + 1, res.end()) - res.begin();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    P3478();
}