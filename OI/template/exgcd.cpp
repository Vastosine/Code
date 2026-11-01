#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

#define ll long long

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll x0, y0;
    ll g = exgcd(b, a % b, x0, y0);
    x = y0;
    y = x0 - a / b * y0;
    return g;
}

int main() {
    for (ll a = -50; a <= 50; a++) {
        for (ll b = -50; b <= 50; b++) {
            if (!a && !b) continue;
            ll x, y, g = exgcd(a, b, x, y);
            assert(a * x + b * y == g);
            assert(g > 0);
        }
    } 
}