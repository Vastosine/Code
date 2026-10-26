// brute reference for 2277D2 (Number Operating, Hard)
//   input : t, then t lines "l r"        (same as the real problem)
//   output: one line per test case, sum of f(x) for x in [l, r], mod 998244353
//
// f is the recurrence verified against D1 (AC):
//   f(0) = 0, f(1) = 1, f(2) = 3
//   k   = smallest with (1<<k)-1 >= x
//   f(x)= k                                if x == (1<<k)-1
//         min((1<<k)-1-x+k, f(x-(1<<(k-1))+2)+k)   otherwise
// Keep r small (<= 2e6): this is O(r) per test case.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll M = 998244353;

static vector<ll> memo;

ll f(ll x) {
    if (x == 0) return 0;
    if (x < (ll)memo.size() && memo[x]) return memo[x];
    ll k = 1;
    while (((1LL << k) - 1) < x) k++;
    ll res;
    if (((1LL << k) - 1) == x) res = k;
    else res = min(((1LL << k) - 1) - x + k, f(x - (1LL << (k - 1)) + 2) + k);
    if (x < (ll)memo.size()) memo[x] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    vector<pair<ll, ll>> qs(t);
    ll mx = 0;
    for (auto &q : qs) {
        cin >> q.first >> q.second;
        mx = max(mx, q.second);
    }
    memo.assign(mx + 2, 0);
    memo[1] = 1;
    if (mx >= 2) memo[2] = 3;

    for (auto &q : qs) {
        ll sum = 0;
        for (ll x = q.first; x <= q.second; x++) sum = (sum + f(x)) % M;
        cout << sum << "\n";
    }
    return 0;
}
