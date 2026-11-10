// Problem : F. Graph Without Long Directed Paths https://codeforces.com/problemset/problem/1144/F
// Time    : 2026-11-10 14:09:48
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

// storage e with v and id/-id 
// col[1] = 1; (col = 1 or 2)
// bfs (start from 1) for u, for v in e[u], if (col[v] && col[v] == col[u]) return false
//                           if (!col[v]) col[v] = 3 - col[u];

string Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> e(n + 1);
    vi col(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back({v, i});
        e[v].push_back({u, -i});
    }
    vi o(1, 1);
    col[1] = 1;
    for (int i = 0; i < n; i++) {
        int u = o[i];
        for (auto &[v, w] : e[u]) {
            if (col[v] == col[u]) return "";
            if (!col[v]) col[v] = 3 - col[u], o.push_back(v);
        }
    }
    string ans(m, '0');
    for (int u : o) {
        if (col[u] == 1) {
            for (auto &[v, w] : e[u]) {
                if (w > 0) ans[w - 1]++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
