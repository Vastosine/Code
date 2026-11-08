// Problem : C. Travelling Salesman and Special Numbers https://codeforces.com/problemset/problem/914/C
// Time    : 2026-11-08 18:44:25
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

const int M = 1e9 + 7;

// State: f[n][m][tight]: n digits, m '1's, 
// Transfer: f[i + 1][j + x][t && x == a[i]] += f[i][j][t], x from 0 to (t ? a[i] : 1)
// Complexity: 1000 * 1000 * 2 * 2
// Border: f[0][0][1] = 1
// Remember mod  
auto Main([[maybe_unused]] int C = 0) {
    string s;
    int k;
    cin >> s >> k;
    if (!k) return 1ll;
    int n = (int) s.length();
    vector<vector<vll>> f(n + 1, vector<vll>(n + 1, vll(2)));
    f[0][0][1] = 1;
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        for (int j = 0; j <= i; j++) {
            for (int t = 0; t < 2; t++) {
                for (int x = 0; x <= (t ? c : 1) && j + x <= n; x++) {
                    (f[i + 1][j + x][t && x == c] += f[i][j][t]) %= M;
                }
            }
        }
    }
    vector<int> step(n + 1);
    step[1] = 1;
    for (int i = 1; i <= n; i++) {
        step[i] = step[__builtin_popcount(i)] + 1;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) if (step[i] - 1 == k) (ans += f[n][i][0] + f[n][i][1]) %= M;
    if (k == 1) (ans += M - 1) %= M; 
    // vector<vll> g(k + 1, vll(n + 1));
    // for (int i = 2; i <= n; i++) g[1][i] = f[n][i][0] + f[n][i][1];
    // for (int i = 2; i <= k; i++) {
    //     for (int j = 2; j <= n; j++) {
    //         (g[i][__builtin_popcount(j)] += g[i - 1][j]) %= M;
    //     }
    // }
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
