// Problem : D. Substring https://codeforces.com/problemset/problem/919/D
// Time    : 2026-11-10 15:52:59
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
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

// State: f[i][c] : end of i, character c max count
// Transfer: for u (in[u] = 0)(f[u][s[u]]++) to v (in[v] != 0), in[v]--, f[v][c] = max(f[v][c], f[u][c]), c in [0, 26)
// Complexity: 3e5 * 26
// Border: ans = -1 if exsisting one vertice without being visited
auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> e, f(n + 1, vi(26));
    vi in, a;
    assign(n + 1, e, in, a);
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        a[i] = c - 'a';
    }
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        in[v]++;
    }
    vi o;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) o.push_back(i);
    }
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        f[u][a[u]]++;
        for (int v : e[u]) {
            in[v]--;
            if (!in[v]) o.push_back(v);
            for (int c = 0; c < 26; c++) {
                f[v][c] = max(f[v][c], f[u][c]);
            }
        }
    }
    if ((int) o.size() < n) return -1;
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int x : f[u]) ans = max(ans, x);
    }
    return ans;
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
