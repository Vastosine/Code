#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"

mt19937_64 rng;

ll rnd(ll l, ll r) {          // [l, r], both inclusive
    return l + (ll)(rng() % (unsigned ll)(r - l + 1));
}

void Main() {
    ll n = rnd(5, 10), m = rnd(10, 2e9), k = rnd(2, n);
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < n; i++) {
        cout << rnd(1, 1e9) << " ";
    }
    cout << endl;
}

int main(int argc, char **argv) {
    if (argc < 2) { fprintf(stderr, "usage: gen <seed>\n"); return 1; }
    rng.seed(strtoull(argv[1], nullptr, 10));
    int c = 10;
    cout << c << "\n";
    while (c--) Main();
    return 0;
}
