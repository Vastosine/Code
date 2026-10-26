// generator for 1455D stress tests -- small n, small values, so the BFS
// brute stays cheap.
//   usage: gen1455.exe <seed>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;
static ll rnd(ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); }

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    int t = (int)rnd(1, 4);
    cout << t << "\n";
    while (t--) {
        int n = (int)rnd(2, 7);
        int maxv = (int)rnd(2, 10);
        cout << n << " " << rnd(1, maxv) << "\n";
        for (int i = 0; i < n; i++) cout << rnd(1, maxv) << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}

