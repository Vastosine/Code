// Problem : C. George and Job https://codeforces.com/problemset/problem/467/C
// Time    : 2026-10-27 12:25:54
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n + 1), s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
        if (i >= m) s.push_back(a[i] - a[i - m]);
    }
    int N = n - m + 1;
    vector<vector<ll>> f(N, vector<ll>(k + 1, 0));
    for (int i = 0; i < N; i++) {
        f[i][1] = s[i];
    }
    for (int r = 2; r <= k; r++) {
        ll ans = 0;
        for (int i = m; i < N; i++) {
            f[i][r] = (ans = max(ans, f[i - m][r - 1])) + s[i];
        }
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, f[i].back());
    }
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