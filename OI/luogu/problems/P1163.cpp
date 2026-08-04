#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    double l = 0, r = 3;
    while (r - l > 0.0001) {
        double mid = (l + r) / 2;
        double ans = a;
        for (int i = 0; i < c; i++) {
            ans = ans * (1 + mid) - b;
        }
        if (ans <= 0) l = mid;
        else r = mid;
    }
    cout << std::fixed << std::setprecision(1) << l * 100;
}