#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

ll popcnt(ll x) { return __builtin_popcountll(x); }

void c1(int n, int m, int k, int q) {
    vector<vector<pll>> e;
    vi col, dep, light;
    vll dis, cmask;
    assign(n + 1, e, light, col, dis, dep, cmask);
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        light[i] = c - '0';
    }
    auto FC = [] (int c) { return 1ll << (c - 1); };
    for (int i = 1; i <= n; i++) cin >> col[i], cmask[i] = FC(col[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[u].push_back({v, w}); e[v].push_back({u, w});
    }
    const int D = __lg(n) + 1;
    vector<vi> fa(n + 1, vi(D + 1));
    vi o(1, 1);
    fa[1][0] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (auto &[v, w] : e[u]) {
            if (!fa[v][0]) {
                fa[v][0] = u;
                dis[v] = dis[u] + w;
                o.push_back(v);
                dep[v] = dep[u] + 1;
                cmask[v] ^= cmask[u];
            }
        }
    }
    for (int d = 0; d < D; d++) {
        for (int u = 1; u <= n; u++) {
            fa[u][d + 1] = fa[fa[u][d]][d];
        }
    }
    auto LCA = [&] (int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int d = D; ~d; d--) {
            int nu = fa[u][d];
            if (dep[nu] >= dep[v]) u = nu;
        }
        if (u == v) return u;
        for (int d = D; ~d; d--) {
            int nu = fa[u][d], nv = fa[v][d];
            if (nu != nv) u = nu, v = nv;
        }
        return fa[u][0];
    };
    auto getDis = [&] (int u, int v, int x = 0) {
        if (!x) x = LCA(u, v);
        return dis[u] + dis[v] - 2 * dis[x];
    };
    auto getmask = [&] (int u, int v, int x = 0) {
        if (!x) x = LCA(u, v);
        return cmask[u] ^ cmask[v] ^ FC(col[x]);
    };
    auto check = [&] (int u, int v) {
        int x = LCA(u, v);
        return getDis(u, v, x) % k == 0 && popcnt(getmask(u, v, x)) == 1;
    };
    vector<vi> f(n + 1, vi(n + 1));
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            f[i][j] = f[j][i] = check(i, j);
            ans += f[i][j] && light[i] && light[j];
        }
        // cout << f[i] << "\n";
    }
    cout << ans << "\n";
    while (q--) {
        int x;
        cin >> x;
        for (int i = 1; i <= n; i++) {
            if (i == x || (light[i] && f[x][i])) ans += light[x] ? -1 : 1;
        }
        light[x] ^= 1;
        cout << ans << "\n";
    }
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    c1(n, m, k, q);
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
