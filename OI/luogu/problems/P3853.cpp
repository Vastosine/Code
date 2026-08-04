#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int L, n, k;
    cin >> L >> n >> k;
    vector<int> a(n), b(n - 1);
    for (int &i : a) cin >> i;
    for (int i = 1; i < n; i++) {
        b[i - 1] = a[i] - a[i - 1] - 1;
    };
    int l = 0, r = L + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        int ans = 0;
        for(int i : b) ans += i / mid;
        if (ans <= k) r = mid;
        else l = mid;
    }
    cout << r;
}