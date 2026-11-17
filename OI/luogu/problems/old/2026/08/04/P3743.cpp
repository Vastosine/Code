#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    long long n, p, sum = 0;
    cin >> n >> p;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i], sum += a[i];
    if (sum <= p) return cout << -1, 0;
    double l = 0, r = 1e10;
    while (r - l > 1e-5) {
        double mid = (l + r) / 2;
        double energy = mid * p;
        for (int i = 0; i < n; i++) {
            energy -= std::max(0.0, a[i] * mid - b[i]);
        }
        if (energy < 0) r = mid;
        else l = mid;
    }
    cout << l;
}