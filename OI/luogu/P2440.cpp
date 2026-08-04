#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    long long n, k, sum = 0;
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a) cin >> i, sum += i;
    if (sum < k) return cout << 0, 0;
    int l = 1, r = 1e8 + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        long long ans = 0;
        for (int i : a) ans += i / mid;
        if (ans < k) r = mid;
        else l = mid;
    }
    cout << l;
}