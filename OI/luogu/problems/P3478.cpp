// Problem : P3478 [POI 2008] STA-Station https://www.luogu.com.cn/problem/P3478
// Time    : 2026-11-21 09:02:50
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<vi> e;
    vll o(1, 1), dep, siz, sum, fa, res;
    assign(n + 1, e, dep, siz, sum, fa, res);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        int u = o[i];
        siz[u] = 1;
        for (int v : e[u]) {
            if (!siz[v]) {
                o.push_back(v);
                dep[v] = dep[u] + 1;
                fa[v] = u;
            }
        }
    }
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        if (fa[u]) {
            siz[fa[u]] += siz[u];
            sum[fa[u]] += sum[u] + siz[u];
        }
    }
    for (int u : o) {
        if (u == 1) res[u] = sum[u];
        else {
            ll stream = (res[fa[u]] - sum[u] - siz[u]) + (n - siz[u]);
            res[u] = sum[u] + stream;
        }
    }
    return max_element(res.begin() + 1, res.end()) - res.begin(); 
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
