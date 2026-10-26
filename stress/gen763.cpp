// generator for 763A stress tests -- small trees, few colours, so that
// multiple "bad" edges (c[u] != c[v]) show up often.
//   usage: gen763.exe <seed>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static mt19937_64 rng;

int main(int argc, char **argv) {
    ll seed = (argc > 1) ? atoll(argv[1]) : 1;
    rng.seed((unsigned long long)seed * 6364136223846793005ULL + 1442695040888963407ULL);

    int n = 2 + (int)(rng() % 8);          // 2..9
    cout << n << "\n";
    for (int v = 2; v <= n; v++) {
        // random parent, but bias towards a path sometimes to create long runs
        int p = (rng() % 3 == 0) ? v - 1 : 1 + (int)(rng() % (v - 1));
        cout << p << " " << v << "\n";
    }
    int colours = 2 + (int)(rng() % 3);    // 2..4
    for (int i = 1; i <= n; i++) cout << 1 + (int)(rng() % colours) << (i == n ? '\n' : ' ');
    return 0;
}
