#include <random>
#include <string>

using namespace std;
typedef long long ll;

mt19937_64 rng;
ll rnd(ll l, ll r) { return rng() % (r - l + 1) + l; }

struct Case {
    ll n, t;
    Case() : n(2000), t(2000) {}
    Case(int x) : n(1ll << x), t(100) {}
    Case(int x, int y) : n(x), t(y) {}
};

string gen(const Case &C, ll seed) {
    rng.seed(seed);
    ll n = C.n;
    ll l = rnd(1, n), r = rnd(l, n);
    return to_string(l) + " " + to_string(r) + "\n";
}