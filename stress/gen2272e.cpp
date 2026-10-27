// generator for 2272E stress tests -- short strings, at least one R each.
//   usage: gen2272e.exe <seed>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;
static ll rnd(ll lo, ll hi) { return lo + (ll)(rng() % (unsigned long long)(hi - lo + 1)); }

static string mk(int len) {
    string r;
    for (int i = 0; i < len; i++) r.push_back(rnd(0, 1) ? 'W' : 'R');
    if (r.find('R') == string::npos) r[rnd(0, len - 1)] = 'R';
    return r;
}

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    int t = (int)rnd(1, 3);
    cout << t << "\n";
    while (t--) {
        int n = (int)rnd(1, 7), m = (int)rnd(1, 7);
        cout << n << " " << m << "\n" << mk(n) << "\n" << mk(m) << "\n";
    }
    return 0;
}

