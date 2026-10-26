// generator for 2277D2 stress tests
//   usage: gen_d2.exe <seed>
//   output: t, then t lines "l r" with small r so brute_d2 stays fast
//
// Deliberately mixes in the boundaries that usually break the fast solution:
//   * l == r
//   * r == 2^k - 1  and  r == 2^k
//   * ranges that straddle a level boundary
//   * one big-ish range near the top of the small table
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;

ll rnd(ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); }

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    const ll CAP = 2000000;  // brute is O(r)
    int t = (int)rnd(1, 4);
    vector<pair<ll, ll>> qs;
    for (int i = 0; i < t; i++) {
        int kind = (int)rnd(0, 5);
        ll l, r;
        if (kind == 0) {                       // single point
            l = r = rnd(1, CAP);
        } else if (kind == 1) {                // straddle a level boundary 2^k - 1
            int k = (int)rnd(1, 20);
            ll b = (1LL << k) - 1;
            l = max(1LL, b - rnd(0, 50));
            r = min(CAP, b + rnd(0, 50));
        } else if (kind == 2) {                // exactly a full level
            int k = (int)rnd(1, 15);
            l = (1LL << (k - 1));
            r = (1LL << k) - 1;
        } else if (kind == 3) {                // short window anywhere
            l = rnd(1, CAP);
            r = min(CAP, l + rnd(0, 20));
        } else if (kind == 4) {                // prefix from 1
            l = 1;
            r = rnd(1, CAP);
        } else {                               // long range
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
