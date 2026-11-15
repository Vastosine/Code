#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

const int M = 1e9 + 7;

ll qpow(ll x, ll n) {
    x = (x % M + M) % M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

vll F;
void init() {
    int n = 1e6;
    F.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % M;
}

ll Cnk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return F[n] * inv(F[k] * F[n - k] % M) % M;
}

int main() {
    ll x, n;
    cin >> x >> n;
    cout << qpow(x, n) << "\n" << inv(x);
}

// 2min