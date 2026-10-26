// generator for 2277D2 in the BIG range (l, r up to 1e18)
//   usage: gen_d2_big.exe <seed>
//
// Pairs with brute_d2_big.cpp.  Focuses on the regime where a 32-bit or even a
// careless 64-bit product inside the fast solution overflows:
//   * r at the very top (1e18, and 2^59 - 1)
//   * ranges straddling a level boundary 2^k - 1 for large k
//   * full levels, full prefixes, single points, adjacent pairs
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;

static ll rnd(ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); }

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    const ll CAP = 1000000000000000000LL;  // 1e18
    int t = (int)rnd(1, 5);
    vector<pair<ll, ll>> qs;
    for (int i = 0; i < t; i++) {
        int kind = (int)rnd(0, 6);
        ll l, r;
        if (kind == 0) {                     // single point, anywhere
            l = r = rnd(1, CAP);
        } else if (kind == 1) {              // straddle 2^k - 1
            int k = (int)rnd(30, 59);
            ll b = (1LL << k) - 1;
            l = max(1LL, b - rnd(0, 3000));
            r = min(CAP, b + rnd(0, 3000));
        } else if (kind == 2) {              // exactly one level
            int k = (int)rnd(30, 59);
            l = (1LL << (k - 1));
            r = (1LL << k) - 1;
        } else if (kind == 3) {              // prefix from 1
            l = 1;
            r = rnd(CAP / 2, CAP);
        } else if (kind == 4) {              // top of the domain
            l = CAP - rnd(0, 5000);
            r = CAP;
        } else if (kind == 5) {              // short window
            l = rnd(1, CAP);
            r = min(CAP, l + rnd(0, 50));
        } else {                             // long range
            l = rnd(1, CAP / 2);
            r = rnd(l, CAP);
        }
        if (l > r) swap(l, r);
        qs.push_back({l, r});
    }
    cout << t << "\n";
    for (auto &q : qs) cout << q.first << " " << q.second << "\n";
    return 0;
}
