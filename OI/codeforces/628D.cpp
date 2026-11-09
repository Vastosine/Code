// Problem : D. Magic Numbers https://codeforces.com/problemset/problem/628/D
// Time    : 2026-11-09 11:55:29
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
ll S(const string &s, int m, int d) {
    int n = (int) s.length();
    vector<vll> ept(vector<vll>(m, vll(2)));
    vector<vector<vll>> f(2, ept);
    f[0][0][1] = 1;
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        f[(i + 1) % 2] = ept;
        for (int j = 0; j < m; j++) {
            for (int t = 0; t < 2; t++) {
                for (int x = 0; x <= (t ? c : 9); x++) {
                    if ((i % 2) ^ (x != d)) {
                        (f[(i + 1) % 2][(j * 10 + x) % m][t && x == c] += f[(i) % 2][j][t]) %= M;
                    }
                }
            }
        }
    }
    return (f[n % 2][0][0] + f[n % 2][0][1]) % M;
}

bool check(const string &s, int m, int d) {
    ll x = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        if ((i % 2) ^ (s[i] - '0' == d)) return false;
        x = (x * 10 + s[i] - '0') % m;
    }
    return !x;
}

// State: f[n][k][tight]: n digits (from high to low), mod m = k, whether tight
// Transfer: f[i + 1][(j * 10 + x) % m][t && x == a[i]] += f[i][j][t];
//           x is not d when 2|i, while x is d otherwise
// Complexity: 2000 * 2000 * 2 * 9
// Border: f[0][0][1] = 1
// Calculate: S(r) - S(l) + check(l)
//            S(s) = f[n][0][0] + f[n][0][1]
// Remember mod 1e9 + 7 and Roll
auto Main([[maybe_unused]] int C = 0) {
    int m, d;
    string l, r;
    cin >> m >> d >> l >> r;
    return ((S(r, m, d) - S(l, m, d) + check(l, m, d)) % M + M) % M;
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
