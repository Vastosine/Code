#include <iostream>

using std::cin;
using std::cout;

typedef long long ll;

ll f(ll a, ll n, ll m) {
    return n > 0 ? f(a * a % m, n / 2, m) * (n % 2 ? a : 1) % m : 1;
}

int main() {
    ll a, n, m;
    cin >> a >> n >> m;
    if (m == -1) return 0;
    cout << f(a, n, m) << std::endl;
    main();
}