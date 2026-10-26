// big-range reference for 2277D2 -- independent in ARITHMETIC only.
//
//   input : t, then t lines "l r"      (l, r up to 1e18)
//   output: one line per test case, sum of f(x) for x in [l, r] mod 998244353
//
// Why this exists: brute_d2.cpp is O(r), so it can only cover r <= ~2e6, where
// no overflow is possible.  The interesting regime is r ~ 2^59, which is
// exactly where `m * k` overflows inside the fast solution.
//
// This reference uses the same level decomposition as the solution but does
// ALL arithmetic in __int128 with NO intermediate modulo -- so an overflow or
// a premature `% M` in the solution shows up as a mismatch.  It is NOT
// independent of the derivation, only of the arithmetic.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

static const ll MOD = 998244353;

static ll gap(int k) { return (1LL << k) - 1; }

static ll levelOf(ll x) {
    int k = 1;
    while (gap(k) < x) k++;
    return k;
}

// f values are <= ~64, no overflow anywhere
static ll f(ll x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x == 2) return 3;
    ll k = levelOf(x);
    if (gap(k) == x) return k;
    return min(gap(k) - x + k, f(x - gap(k - 1) + 1) + k);
}

// cnt[k] = how many of the top values of level k take the A branch
static ll cntTab[64];

static void buildCnt() {
    for (int k = 1; k <= 61; k++) {
        ll x0 = (1LL << k);  // one past the top of level k
        ll c = 0;
        while (c < (1LL << (k - 1))) {
            ll x = x0 - (c + 1);  // top, top-1, ...
            ll A = gap(k) - x + k;
            ll B = f(x - gap(k - 1) + 1) + k;
            if (A > B) break;
            c++;
        }
        cntTab[k] = c;
    }
}

static unordered_map<ll, lll> memo;

// S(n) = sum_{x=0}^{n} f(x), exact (no modular reduction)
static lll Ssum(ll n) {
    if (n <= 0) return 0;
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;

    ll k = levelOf(n);
    ll top = gap(k);
    ll c = cntTab[k];
    lll res;

    if (n > top - c) {  // A branch: differs from the level top by < c positions
        ll d = n - (top - c);
        ll st = k + top - n;              // A(n), the smallest of these terms
        res = Ssum(top - c) + (lll)d * (2LL * st + (d - 1)) / 2;
    } else {            // B branch: recurse one level down
        ll m = n - gap(k - 1);
        res = Ssum(gap(k - 1)) + (lll)k * m + (Ssum(m + 1) - 1);
    }

    memo[n] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildCnt();

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        lll ans = Ssum(r) - Ssum(l - 1);
        cout << (ll)(((ans % MOD) + MOD) % MOD) << "\n";
    }
    return 0;
}
