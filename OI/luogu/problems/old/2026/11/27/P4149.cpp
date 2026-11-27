// Problem : P4149 [IOI 2011] Race https://www.luogu.com.cn/problem/P4149
// Time    : 2026-11-27 19:36:58
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp> 
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

class TreeDivide {
  public:
    TreeDivide(szt n) : n(n), e(n), siz(n), fa(n), vis(n), dis(n) {}

    void addEdge(szt u, szt v, ll w = 1) {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    szt getCentroid(szt s = 1) {
        vst o(1, s);
        fa[s] = s;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            siz[u] = 1;
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v)) {
                    o.push_back(v);
                    fa[v] = u;
                }
            }
        }
        for (szt i = o.size() - 1; i; i--) {
            szt u = o[i];
            siz[fa[u]] += siz[u];
        }
        szt N = siz[s];
        bool change;
        do {
            change = false;
            for (auto &[v, w] : e[s]) {
                if (isSon(s, v) && siz[v] > N / 2) {
                    change = true;
                    s = v;
                    break;
                }
            }
        } while (change); 
        return s;
    }
    
    szt run(szt start = 1) {
        vis.assign(n, 0);
        vst o(1, getCentroid(start));
        szt ans = 0;
        for (szt i = 0; i < o.size(); i++) {
            szt s = o[i];
            vis[s] = 1;
            ans += calculate(s);
            for (auto &[v, w] : e[s]) {
                if (!vis[v]) o.push_back(getCentroid(v));
            }
        }
        return ans;
    }

    virtual szt calculate(szt rt) {
        calcInit(rt);
        szt ans = self(rt);
        for (auto &[s, w] : e[rt]) {
            if (!vis[s]) {
                fa[s] = rt;
                ans += calcSub(s, w);
            }
        }
        return ans;
    }

    virtual void calcInit(szt) {};
    virtual szt self(szt) { return 0; }
    virtual szt calcSub(szt s, ll d) = 0;

    vst getSubOrder(szt s, ll d) {
        vst o(1, s);
        dis[s] = d;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v)) dis[v] = dis[u] + w, o.push_back(v), fa[v] = u;
            }
        }
        return o;
    }

  protected:
    bool isSon(szt u, szt v) const { return !vis[v] && fa[u] != v; }

    szt n;
    vector<vector<pair<szt, ll>>> e;
    vst siz, fa;
    vb vis;
    vll dis;
};

class Race : public TreeDivide {
  public:
    Race(szt n, szt k) : TreeDivide(n), k(k), dep(n) {}

    void calcInit(szt) override { least.clear(), least[0] = 0; }

    szt calcSub(szt s, ll d) override {
        vst o = getSubOrder(s, d);
        dep[fa[s]] = 0;
        for (szt u : o) {
            dep[u] = dep[fa[u]] + 1;
            if (auto it = least.find(k - (szt) dis[u]); it != least.end()) {
                ans = min(ans, dep[u] + it->second);
            }
        }
        for (szt u : o) {
            if (auto it = least.find(dis[u]); dis[u] <= k && (it == least.end() || dep[u] < it->second)) {
                least[dis[u]] = dep[u];
            }
        }
        return 0;
    }

    ll run() {
        TreeDivide::run();
        return ans == INF ? -1 : (ll) ans;
    }
  private:
    szt k, ans = INF;
    vst dep;
    __gnu_pbds::gp_hash_table<szt, szt> least;
};

auto Main(int = 0) {
    szt n, k;
    cin >> n >> k;
    Race g(n, k);
    for (szt i = 1; i < n; i++) {
        szt u, v;
        ll w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    return g.run();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
