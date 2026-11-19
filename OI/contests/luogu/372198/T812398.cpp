// Problem : T812398 [ICPC 2026 Nanchang I] Eating Cherries https://www.luogu.com.cn/problem/T812398?contestId=372198
// Time    : 2026-11-19 13:00:04
#include <algorithm>
#include <iostream>
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

void Min(int &x, int y) { x = min(x, y); }

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> e(n + 1), s(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            a[i] |= (1 << (x - 1));
        }
    }
    vi o(1, 1), fa(n + 1);
    const int M = 1 << m;
    vector<vi> f(n + 1, vi(M, inf)), h(n + 1, vi(M, inf));
    fa[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!fa[v]) fa[v] = u, o.push_back(v), s[u].push_back(v);
        }
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        if (s[u].empty()) {
            for (int j = 0; j < M; j++) {
                f[u][j] = a[u] != j;
            }
        } else {
            vector<vi> g(M, vi(s[u].size(), inf));
            vi ans1(M, 1), ans0(M);
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < (int) s[u].size(); k++) {
                    int v = s[u][k];
                    Min(g[j | a[u]][k], f[v][j]);
                }
            }
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < (int) s[u].size(); k++) {
                    if (ans0[j] == inf || g[j][k] == inf) ans0[j] = inf;
                    else ans0[j] += g[j][k];
                }
            }
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < (int) s[u].size(); k++) {
                    ans1[j] += h[s[u][k]][j];
                }
                f[u][j] = min(ans1[j], ans0[j]);
            }
        }
        for (int j = 0; j < M; j++) {
            for (int k = j; ; k = (k - 1) & j) {
                Min(h[u][j], f[u][k]);
                if (!k) break;
            }
            // if (j >= (1 << k)) k++;
            // Min(h[u][j], f[u][j]);
            // Min(h[u][j | (1 << k)], h[u][j]);
        } 
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j < M; j++) {
    //         cout << (f[i][j] == inf ? -1 : f[i][j]) << " ";
    //     }
    //     cout << "\n";
    // }
    vi ans(n + 1, inf);
    ans[1] = *min_element(f[1].begin(), f[1].end());
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < M; j++) {
            Min(ans[i], f[fa[i]][j] - f[i][j])
        }
    }
    return 0;
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
