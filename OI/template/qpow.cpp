#include <iostream>
#define ll long long

using namespace std;

const int M = 1e9 + 7;

ll qpow(ll x, ll n) {
    x = (x % M + M) % M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

int main() {
    ll x, n;
    cin >> x >> n;
    cout << qpow(x, n) << "\n" << inv(x);
}

// 2min