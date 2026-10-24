#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"

mt19937_64 rng;

ll rnd(ll l, ll r) {          // [l, r], both inclusive
    return l + (ll)(rng() % (unsigned ll)(r - l + 1));
}

void Main() {
    int k = rnd(1, 200), l = rnd(1, 200), r = rnd(l, 200);
    cout << k << " " << l << " " << r << "\n";
    for (int i = 0; i < k; i++) {
        int p = rnd(l, r);
        while (p--) cout << (char) rnd('a', 'z');
    }
}

int main(int argc, char **argv) {
    if (argc < 2) { fprintf(stderr, "usage: gen <seed>\n"); return 1; }
    rng.seed(strtoull(argv[1], nullptr, 10));
    int c = 1;
    // cout << c << "\n";
    while (c--) Main();
    return 0;
}
