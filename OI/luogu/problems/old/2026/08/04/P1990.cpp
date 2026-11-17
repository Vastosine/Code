#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const int M = 10000;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    a[0] = a[1] = 1;
    for (int i = 2; i <= n; i++) {
        a[i] = (a[i - 1] + b[i - 1] + a[i - 2]) % M;
        b[i] = (b[i - 1] + a[i - 2] * 2) % M;
        // cout << a[i] << " " << b[i] << "\n";
    }
    cout << a[n];
}