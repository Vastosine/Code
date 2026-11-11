#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
const ll INF = 1ll << 60;

vector<vi> e;
vi to;
vll a;
int n;

ll Dinic(int s, int t) {
    if (s == t) return -1;
    ll ans = 0;
    while (true) {
        vi dep(n + 1), cur(n + 1);
        vi o(1, s);
        dep[s] = 1;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j : e[u]) {
                int v = to[j];
                if (!dep[v] && a[j]) {
                    dep[v] = dep[u] + 1;
                    o.push_back(v);
                }
            }
        }
        if (!dep[t]) return ans;
        auto dfs = [&] (auto &&f, int u, ll limit = INF) {
            if (u == t || !limit) return limit;
            ll ret = 0;
            for (; cur[u] < (int) e[u].size() && ret < limit; cur[u]++) {
                int id = e[u][cur[u]], v = to[id];
                ll w = a[id];
                if (dep[v] == dep[u] + 1) {
                    ll add = f(f, v, min(limit - ret, w));
                    ret += add;
                    a[id] -= add;
                    a[id ^ 1] += add;
                }
            }
            return ret;
        };
        ans += dfs(dfs, s);
    }
}

int main() {
    int m, s, t;
    cin >> n >> m >> s >> t;
    e.assign(n + 1, {});
    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[u].push_back(to.size());
        to.push_back(v);
        a.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        a.push_back(0);
    }
    cout << Dinic(s, t);
}