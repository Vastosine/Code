// Problem : E. Graph Cutting https://codeforces.com/contest/2231/problem/E
// Time    : 2026-11-21 15:20:06
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
    int n, d;
    cin >> n >> d;
    vector<vi> e, s;
    vi dep, fa, o(1, 1);
    assign(n + 1, e, s, dep, fa);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dep[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!dep[v]) dep[v] = dep[u] + 1, o.push_back(v), fa[v] = u, s[u].push_back(v);
        }
    }
    vector<vll> up(n + 1, vll(d + 1)), down(n + 1, vll(d + 1));
    for (int i = n - 1; ~i; i--) {
        int u = o[i];
        down[u][0] = 1;
        if (u != 1) for (int j = 0; j < d; j++) {
            down[fa[u]][j + 1] += down[u][j];
        }
    }
    for (int u : o) {
        up[u][0] = 1;
        if (u != 1) for (int j = 0; j < d; j++) {
            up[u][j + 1] += up[fa[u]][j];
            if (j) up[u][j + 1] += down[fa[u]][j] - down[u][j - 1]; 
        }
    }
    auto getOrder = [&] (int u) {
        vi o(1, u);
        for (int i = 0; i < (int) o.size(); i++) {
            for (int v : s[o[i]]) o.push_back(v);
        }
        return o;
    };
    ll ans0 = 0, ans1 = 0, ans2 = 0;
    for (int u : o) {
        for (int v : s[u]) {
            for (int j = 0; j < d - 2; j++) {
                ans0 += down[v][d - j - 3] * (down[u][j + 1] - down[v][j]);
            }
        }
        ans0 += down[u][d - 1] * 2;
    }
    for (int u : o) {
        if (s[u].size() < 2) continue;
        for (int i = 0; i < (int) s[u].size(); i++) {
            int p = s[u][i];
            vi op = getOrder(p);
            for (int j = i + 1; j < (int) s[u].size(); j++) {
                int q = s[u][j];
                vi oq = getOrder(q);
                for (int v : op) {
                    for (int w : oq) {
                        if (int x = d - 1 - (dep[v] - dep[u]) - (dep[w] - dep[u]); x > 0) {
                            ans1 += up[u][x];
                            ans2 += down[u][x] - down[p][x - 1] - down[q][x - 1];
                        }
                    }
                }
            }
        }
    }
    return ans0 * (d - 2) / 2 + ans1 + ans2 / 3;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
