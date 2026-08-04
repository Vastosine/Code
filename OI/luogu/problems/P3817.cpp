#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    long long ans = 0;
    if (a[0] > m) {
        ans += a[0] - m;
        a[0] = m;
    }
    for (int i = 1; i < n; i++) {
        int x = a[i] + a[i - 1] - m;
        if (x <= 0) continue;
        a[i] -= x;
        ans += x;
    }
    cout << ans;
}