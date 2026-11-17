#include <iostream>

using std::cin;
using std::cout;

int main() {
    long long n, m;
    cin >> n >> m;
    long long x = 0, y;
    for (int i = 0; i < m && i < n; i++) {
        x += (n - i) * (m - i);
    }
    y = n * m * (n + 1) * (m + 1) / 4 - x;
    cout << x << " " << y;
}