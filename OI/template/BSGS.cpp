#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

const int M = 1e9 + 7;
using ll = long long;
using vll = vector<ll>;

ll qpow(ll x, ll n, int m = M) {
    x = (x % m + m) % m;
    ll res = 1;
    while (n) {
        if (n & 1) (res *= x) %= m;
        x = x * x % m;
        n >>= 1;
    }
    return res % m;
}

// m need to be prime
ll inv(ll x, int m = M) {
    return qpow(x, m - 2, m);
}

int dlog(ll g, ll h, int m = M) {
    int B = sqrt(m);
    unordered_map<int, int> T;
    ll x = qpow(g, B, m);
    for (ll y = 1, i = 0; i <= B; i++, y = y * x % m) {
        T[y] = i;
    }
    ll invh = inv(g, m);
    for (ll i = 0, y = h; i < B; i++, y = y * invh % m) {
        if (T.find(y) != T.end()) return i + B * T[y];
    }
    return -1;
}