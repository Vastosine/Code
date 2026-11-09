// Problem : F. Number of Subsequences https://codeforces.com/problemset/problem/1426/F
// Time    : 2026-11-08 08:40:16
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

// State f[i][j] first i characters, count of a / ab / abc (j = 1 / 2 / 3)
// Transfer f[i][j] = f[i - 1][j - 1] * (j == a[i] - 'a' + 1 || s[i] == '?') + f[i][j] * (a[i] == '?' ? 3 : 1) 
// Complexity n
// Border f[0][0] = 1;
auto Main([[maybe_unused]] int C = 0) {
    int n;
    string s;
    cin >> n >> s;
    vector<vector<ll>> f(n + 1, vector<ll>(4, 0));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        char c = s[i - 1];
        f[i][0] = f[i - 1][0] * (c == '?' ? 3 : 1) % M;
        for (int j = 1; j <= 3; j++) {
            f[i][j] = (f[i - 1][j - 1] * (j == c - 'a' + 1 || c == '?') + f[i - 1][j] * (c == '?' ? 3 : 1)) % M; 
        }
    }
    return f[n][3];
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

/**

 *  CHECK Type int * int, int to ll, negative index  : 1
 *  CHECK Vector Size                                : 1
 *  CHECK Multiple Test Clear                        : 1
 *  CHECK Restriction Value remain, border, negative : 1
 *  CHECK Output Format                              : 1

 */