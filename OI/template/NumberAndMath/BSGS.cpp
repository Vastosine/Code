#include <algorithm>
#include <cmath>
#include <unordered_map>
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

int dlog_map(ll g, ll h, int m) {
    int B = sqrt(m);
    unordered_map<int, int> T;
    T.reserve(B + 2);
    ll x = qpow(g, B, m);
    for (ll y = 1, i = 0; i <= B; i++, y = y * x % m) {
        T[y] = i;
    }
    ll invh = inv(g, m);
    for (ll i = 0, y = h; i < B; i++, y = y * invh % m) {
        auto it = T.find(y);
        if (it != T.end()) return i + B * it->second;
    }
    return -1;
}

struct Dlog {
    int B, steps, cap, m;
    ll g;
    vector<int> key, val;
    ll step;                       // g^{-B}
    static unsigned hs(ll y) { return (unsigned) y * 2654435761u >> 8; }

    // N = 要取对数的总个数 = n * q；g0 必须是 mod 的原根
    void init(ll N, ll g0 = 3, int mod = M) {
        g = g0, m = mod;
        B = (int) sqrt((double) N * (m - 1)) + 1;
        steps = (m - 1) / B + 2;
        step = inv(qpow(g, B, m), m);      // g^{-B}
        cap = 1; while (cap < 2 * B) cap <<= 1;
        key.assign(cap, 0); val.assign(cap, 0);
        ll y = 1;
        for (int j = 0; j < B; j++) {
            int pos = hs(y) & (cap - 1);
            while (key[pos]) pos = (pos + 1) & (cap - 1);
            key[pos] = (int) y + 1;   // +1 让 0 当空槽
            val[pos] = j;
            y = y * g % m;
        }
    }
    int operator()(ll h) const {
        ll y = h;
        for (int i = 0; i < steps; i++) {
            int pos = hs(y) & (cap - 1);
            while (key[pos]) {
                if (key[pos] == (int) y + 1) {
                    int x = i * B + val[pos];
                    if (x <= m - 2) return x;    // 溢出 m-1 的是另一个代表元，继续找
                }
                pos = (pos + 1) & (cap - 1);
            }
            y = y * step % m;
        }
        return -1;
    }
};
