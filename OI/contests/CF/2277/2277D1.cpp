// Problem : D1. Number Operating (Easy Version) https://codeforces.com/contest/2277/problem/D1
// Time    : 2026-10-24 19:05:14
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

ll f(ll x) {
    if (x < 4) return (int[]) {0, 1, 3, 2} [x];
    ll k = 0;
    while (x > (1ll << k) - 1) k++;
    if (x == (1ll << k) - 1) return k;
    return min(k + (1ll << k) - 1 - x, f(x + 2 - (1ll << (k - 1))) + k) % M;
}

auto solve() {
    ll l, r;
    cin >> l >> r;
    ll ans = 0;
    for (ll x = l; x <= r; x++) (ans += f(x)) %= M;
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