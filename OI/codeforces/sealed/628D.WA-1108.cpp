// Problem : D. Magic Numbers https://codeforces.com/problemset/problem/628/D
// Time    : 2026-11-08 10:39:13
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

// State: f[i][j]: i digits with mod m = j
// Transfer: f[i + 1][(j * 10 + x) % m] += f[i][j], x = d when 2 | i, otherwise x != d
// Complexity: 2e3 * 2e3
// Border: f[0][0] = 0
// Calculate: init the (10 ^ n) % m. Then calculate with site from high to low
// f(r) - f(l - 1)
auto Main([[maybe_unused]] int C = 0) {
    int m, d;
    string l, r;
    cin >> m >> d >> l >> r;
    int n = (int) l.length();
    vector<vector<ll>> f(n + 1, vector<ll>(m));
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
        if (i & 1) {
            for (int j = 0; j < m; j++) {
                (f[i + 1][(j * 10 + d) % m] += f[i][j]) %= M;
            }
        } else {
            for (int j = 0; j < m; j++) {
                for (int x = 0; x < 10; x++) {
                    if (x == d) continue;
                    (f[i + 1][(j * 10 + x) % m] += f[i][j]) %= M;
                }
            }
        }
    }
    vector<ll> pow10(n + 1, 1);
    for (int i = 1; i <= n; i++) pow10[i] = pow10[i - 1] * 10 % m;
    // calculate all x < int?(s);
    auto F = [&] (const string &s) {
        ll ans = 0, len = (int) s.length(), pre = 0;
        for (int i = 0; i < len; i += 2) {
            if (i < len - 1) (pre += pow10[len - i - 2] * d) %= m;
            for (int j = 0; j < s[i] - '0'; j++) {
                if (j != d) {
                    if (i == len - 1) ans += !pre;
                    else (ans += f[len - i - 2][(m - pre) % m]) %= M;
                }
                (pre += pow10[len - i - 1]) %= m;
            }
            if (i < len - 1 && s[i + 1] - '0' < d) break;
            if (i >= len - 2) {
                (ans += !pre) %= M;
            }
        }
        return ans;
    };
    auto check = [&] (const string &s) {
        ll x = 0;
        for (int i = 0; i < n; i++) {
            if ((i & 1) ^ (s[i] == '0' + d)) return false;
            x = (x * 10 + s[i] - '0') % m;
        }
        return !x;
    };
    return ((F(r) - F(l) + check(r)) % M + M) % M;
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
