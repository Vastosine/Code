// generator for 1946C stress tests -- small trees, so the brute can enumerate
// every set of k cut edges.
//   usage: gen1946.exe <seed>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;
static ll rnd(ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); }

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    int t = (int)rnd(1, 3);
    cout << t << "\n";
    while (t--) {
        int n = (int)rnd(2, 9);
        int k = (int)rnd(1, n - 1);
        cout << n << " " << k << "\n";
        for (int v = 2; v <= n; v++) {
            // bias towards paths so deep chains get exercised
            int p = (rng() % 2) ? v - 1 : 1 + (int)(rng() % (v - 1));
            cout << p << " " << v << "\n";
        }
    }
    return 0;
}
