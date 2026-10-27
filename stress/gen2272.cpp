// generator for 2272C stress tests -- small coordinates.
//   usage: gen2272.exe <seed>
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
        int n = (int)rnd(2, 5);
        int x = (int)rnd(0, 2);
        set<int> used;
        while ((int)used.size() < n) used.insert((int)rnd(0, 10));
        cout << n << " " << x << "\n";
        bool first = true;
        for (int v : used) { cout << (first ? "" : " ") << v; first = false; }
        cout << "\n";
    }
    return 0;
}
