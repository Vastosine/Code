#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

const int M = 1e9 + 7;

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

vll F;
int Cmod = M;  // F 表是用哪个模数建的；Cnk 的默认参数读它，两边不可能对不上
void initCnk(int m = M) {
    Cmod = m;
    int n = 1e6;
    F.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % Cmod;
}

ll Cnk(int n, int k, int m = Cmod) {
    if (k < 0 || k > n) return 0;
    return F[n] * inv(F[k] * F[n - k] % m, m) % m;
}

int main() {
    ll x, n;
    cin >> x >> n;
    cout << qpow(x, n) << "\n" << inv(x);
}

// 2min