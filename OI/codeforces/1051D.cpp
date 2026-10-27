// Problem : D. Bicolorings https://codeforces.com/problemset/problem/1051/D
// Time    : 2026-10-28 07:21:06
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

const int M = 998244353;

int add[4][4] = {
    {0, 1, 1, 1},
    {0, 0, 2, 0},
    {0, 2, 0, 0},
    {1, 1, 1, 0}
};

auto solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<vector<ll>>> f(2, vector<vector<ll>>(k + 3, vector<ll>(4)));
    f[0][1][0] = f[0][1][3] = f[0][2][1] = f[0][2][2] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int t = 0; t < 4; t++) {
                f[i % 2][j][t] = 0;
                for (int s = 0; s < 4; s++) {
                    if (j >= add[s][t]) (f[i % 2][j][t] += f[(i - 1) % 2][j - add[s][t]][s]) %= M;
                }
            }
        }
    }
    ll ans = 0;
    for (ll i : f[(n - 1) % 2][k]) (ans += i) %= M;
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}