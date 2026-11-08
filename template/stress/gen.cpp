#include <random>
#include <string>
#include <utility>

using namespace std;
typedef long long ll;

mt19937_64 rng;
ll rnd(ll l, ll r) { return rng() % (r - l + 1) + l; }

struct Case {
    int n, m;
    Case() : n(2000), m(2000) {}
    Case(int x) : n(x), m(10) {}
    Case(int x, int y) : n(x), m(y) {}
};

string gen(const Case &C, ll seed) {
    rng.seed(seed);
    int m = rnd(1, C.m);
    int n = rnd(1, C.n);
    int d = rnd(0, 9);
    string s = to_string(m) + " " + to_string(d) + "\n";
    string x[2];
    for (int i = 0; i < 2; i++) {
        x[i] += rnd(1, 9) + '0';
        for (int j = 1; j < n; j++) {
            x[i] += rnd(0, 9) + '0';
        }
        x[i] += "\n";
    }
    if (x[0] > x[1]) swap(x[0], x[1]);
    return s + x[0] + x[1];
}