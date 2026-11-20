#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

const int M = 1e9 + 7;
using ll = long long;
using vll = vector<ll>;
using pii = pair<int, int>;

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

int dlog(ll g, ll h, int m) {
    int B = sqrt(m);
    vector<pii> T;
    T.reserve(B + 2);
    ll x = qpow(g, B, m);
    for (ll y = 1, i = 0; i <= B; i++, y = y * x % m) {
        T.push_back({(int) y, (int) i});
    }
    sort(T.begin(), T.end());  // lower_bound 要求有序，g^{B*i} 本身不单调
    ll invh = inv(g, m);
    for (ll i = 0, y = h; i < B; i++, y = y * invh % m) {
        auto it = lower_bound(T.begin(), T.end(), pii{(int) y, 0});
        if (it != T.end() && it->first == y) return i + B * it->second;
    }
    return -1;
}