// Problem : C. Classy Numbers https://codeforces.com/contest/1036/problem/C
// Time    : 2026-11-08 16:09:03
#include <iostream>
#include <string>
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

// State: f[n][k][tight] (from high to low) : n digits, k non-zero, is tight
// Transfer: f[i + 1][j + !!dig][t && dig == c] += f[i][j][t]
// Complexity: 18 * 4 * 2 * 9
// Border: f[0][0][1] = 1

ll solve(string s) {
    int n = (int) s.length();
    vector<vll> ept(3 + 1, vll(2));
    vector<vector<vll>> f(2, ept);
    f[0][0][1] = 1;
    for (int i = 0; i < n; i++) {
        char c = s[i] - '0';
        f[(i + 1) & 1] = ept;
        for (int j = 0; j <= 3; j++) {
            for (int t = 0; t <= 1; t++) {
                for (int dig = 0; dig <= (t ? c : 9); dig++) {
                    int p = j + !!dig;
                    if (p > 3) continue;
                    f[(i + 1) & 1][p][t && dig == c] += f[i & 1][j][t];
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= 3; i++) {
        ans += f[n & 1][i][0] + f[n & 1][i][1];
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    ll l, r;
    cin >> l >> r;
    return solve(to_string(r)) - solve(to_string(l - 1));
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
