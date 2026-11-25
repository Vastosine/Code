#include <cstdlib>
#include <iostream>
#include <set>
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

auto Main([[maybe_unused]] int C = 0) {
    ll n, k, op;
    cin >> n >> k >> op;
    vll a(n);
    cin >> a;
    Sort(a);
    vector<set<ll>> s;
    int p = 0;
    for (ll x : a) {
        bool t = false;
        int sn = (int) s.size();
        for (int q = 0; q < sn; q++) {
            auto &i = s[(p + q) % sn];
            if (auto it = i.upper_bound(x / (k + op) - !op); it == i.end() || x / *it != k) {
                i.insert(x);
                t = true;
                p = (p + q) % sn;
                break;
            }
        }
        if (!t) s.push_back({}), s.back().insert(x);
    }
    // if (s.size() >= 3) {
    //     vector<vi> e(n + 1);
    //     vi f(n + 1);
    //     for (int i = 1, l = 1; i <= n; i++) {
    //         f[i] = i;
    //         while (a[l - 1] < a[i - 1] * k) l++;
    //         for (int j = l; j <= n && a[j - 1] / a[i - 1] == k; j++) {
    //             e[i].push_back(j);
    //             e[j].push_back(i);
    //         }
    //     }
    //     auto g = [&] (auto &&g, int u) -> int {
    //         return f[u] == u ? u : g(g, f[u]);
    //     };
    //     auto merge = [&] (int u, int v) {
    //         f[g(g, v)] = g(g, u);
    //     };
    //     vi vis(n + 1), col(n + 1);
    //     vector<vi> lst(2);
    //     for (int i = 1; i <= n; i++) {
    //         if (!vis[i]) {
    //             vis[i] = 1;
    //             vi o(1, i);
    //             for (int j = 0; j < (int) o.size(); j++) {
    //                 int u = o[j];
    //                 lst[col[u]].push_back(u);
    //                 for (int v : e[u]) {
    //                     if (!vis[v]) {
    //                         vis[v] = 1;
    //                         o.push_back(v);
    //                         col[v] = col[u] ^ 1;
    //                         // auto &X = lst[col[v]];
    //                         // if (!X.empty()) {
    //                         //     merge(X[0], v);
    //                         // }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     bool ans = 1;
    //     for (int u = 1; u <= n; u++) {
    //         for (int v : e[u]) {
    //             if (col[u] == col[v]) ans = 0;
    //         }
    //     }
    //     if (ans) {
    //         cout << 2 << "\n";
    //         for (auto &i : lst) {
    //             cout << i.size() << " ";
    //             for (auto &j : i) cout << a[j - 1] << " ";
    //             cout << "\n";
    //         }
    //         return 0;
    //     }
    // }
    cout << s.size() << "\n";
    for (auto &i : s) {
        cout << i.size() << " ";
        for (auto &j : i) cout << j << " ";
        cout << "\n";
    }
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
