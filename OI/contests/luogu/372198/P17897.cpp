// Problem : P17897 [ICPC 2026 Nanchang I] Journey of GCD https://www.luogu.com.cn/problem/P17897?contestId=372198
// Time    : 2026-11-19 18:41:53
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

vector<vi> e, f, dis;
int n;
vi dep;
int D;

void initLCA(int r = 1) {
    D = __lg(n) + 1;
    f.assign(n + 1, vi(D + 1));
    dis.assign(n + 1, vi(D + 1));
    dep.assign(n + 1, 0);
    vi o(1, r);
    dep[r] = 1;
    f[r][0] = r;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v), f[v][0] = u, dis[v][0] = gcd(u, v);
        }
    }
    dis[r][0] = r;
    for (int d = 0; d < D; d++) {
        for (int u = 1; u <= n; u++) {
            f[u][d + 1] = f[f[u][d]][d];
            dis[u][d + 1] = min(dis[u][d], dis[f[u][d]][d]);
        }
    }
}

int LCA(int u, int v) {
    if (u == v) return u;
    int ans = inf;
    if (dep[u] < dep[v]) swap(u, v);
    for (int d = D; ~d; d--) {
        int nu = f[u][d];
        if (dep[nu] >= dep[v]) ans = min(ans, dis[u][d]), u = nu;
    }
    if (u == v) return ans;
    for (int d = D; ~d; d--) {
        int nu = f[u][d], nv = f[v][d];
        if (nu != nv) ans = min({ans, dis[u][d], dis[v][d]}), u = nu, v = nv;
    }
    return min({ans, dis[u][0], dis[v][0]});
}

auto Main([[maybe_unused]] int C = 0) {
    int N, m;
    cin >> N >> m;
    vi a(N);
    cin >> a;
    n = *max_element(a.begin(), a.end());
    e.assign(n + 1, {});
    vi has(n + 1), fa(n + 1);
    auto getF = [&] (auto &&f, int u) -> int {
        return fa[u] = fa[u] ? fa[u] == u ? u : f(f, fa[u]) : u;
    }; 
    auto merge = [&] (int u, int v) {
        int fu = getF(getF, u), fv = getF(getF, v);
        fa[fu] = fv;
        return fu != fv;
    };
    for (int x : a) has[x] = 1;
    for (int i = n; i; i--) {
        vi lst;
        for (int j = i; j <= n; j += i) {
            if (has[j]) lst.push_back(j);
        }
        for (int j = 1; j < (int) lst.size(); j++) {
            if (int u = lst[j], v = lst[j - 1]; merge(u, v)) {
                e[u].push_back(v);
                e[v].push_back(u);
                // cout << u << " " << v << "\n";
            }
        }
    }
    initLCA(a[0]);
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(a[u - 1], a[v - 1]) << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ns << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
