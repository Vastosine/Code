// Problem : G. Good Key, Bad Key https://codeforces.com/problemset/problem/1703/G
// Time    : 2026-10-27 10:20:31
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

auto solve() {
    int n, k;
    cin >> n >> k;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<ll>> f(n + 1, vector<ll>(32, NEG));
    f[0][0] = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 32; j++) {
            f[i][j] = max(f[i - 1][j] + a[i] / (1ll << j) - k, j ? f[i - 1][j - 1] + a[i] / (1ll << j) : NEG);
            ans = max(ans, f[i][j]);
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}