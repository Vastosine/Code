// Problem : P4174 [NOI2006] 最大获利 https://www.luogu.com.cn/problem/P4174
// Time    : 2026-11-28 10:11:31
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? " " : "") << a[i]; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<vector<T>> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? "\n" : "") << a[i]; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

class Dinic {
  public:
    // 0-index
    Dinic(szt n) : n(n), e(n) {}

    void resize(szt N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(szt N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    szt addEdge(szt u, szt v, szt c) { add(u, v, c); add(v, u, 0); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the Dinic, return the max flow.
    szt run(szt s, szt t) {
        szt ans = 0;
        while (true) {
            vst cur(n), dep = reachable(s);
            if (!~dep[t]) return ans;
            auto dfs = [&] (auto &&f, szt u, szt lim = INF) {
                if (!lim || u == t) return lim;
                szt ret = 0;
                for (; cur[u] < e[u].size() && ret < lim; cur[u]++) {
                    if (szt i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1 && cap[i]) {
                        szt add = f(f, v, min(lim - ret, cap[i]));
                        ret += add;
                        cap[i] -= add;
                        cap[i ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    }

    szt flowOn(szt id) const { return cap[id ^ 1]; }

    vst reachable(szt s) const {
        vst o(1, s), dep(n, ~0ull);
        dep[s] = 0;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (szt j : e[u]) {
                if (szt v = to[j]; !~dep[v] && cap[j]) o.push_back(v), dep[v] = dep[u] + 1;
            }
        }
        return dep;
    }

  protected:
    // Add single edge
    void add(szt u, szt v, szt c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    szt n;
    vector<vst> e;
    vst cap, to;
};

auto Main(int = 0) {
    szt n, m;
    cin >> n >> m;
    szt s = n + m, t = s + 1, N = t + 1;
    Dinic g(N);
    for (szt i = 0; i < n; i++) {
        szt x;
        cin >> x;
        g.addEdge(s, i, x);
    }
    szt sum = 0;
    for (szt i = 0; i < m; i++) {
        szt x, y, z;
        cin >> x >> y >> z;
        g.addEdge(i + n, t, z);
        g.addEdge(x - 1, i + n, INF);
        g.addEdge(y - 1, i + n, INF);
        sum += z;
    }
    return sum - g.run(s, t);
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
