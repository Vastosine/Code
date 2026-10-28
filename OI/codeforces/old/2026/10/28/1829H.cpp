// Problem : H. Don't Blame Me https://codeforces.com/problemset/problem/1829/H
// Time    : 2026-10-28 16:20:21
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

const ll M = 1e9 + 7;

auto solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    cin >> a;
    vector<vector<ll>> f(2, vector<ll>(64));
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 64; j++) f[(i + 1) % 2][j] = 0;
        f[(i + 1) % 2][a[i]]++;
        for (int j = 0; j < 64; j++) {
            if (f[i % 2][j]) {
                (f[(i + 1) % 2][j & a[i]] += f[i % 2][j]) %= M;
                (f[(i + 1) % 2][j] += f[i % 2][j]) %= M;
            }
        }
    }
    for (int j = 0; j < 64; j++) {
        if (__builtin_popcount(j) == k) (ans += f[n % 2][j]) %= M;
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