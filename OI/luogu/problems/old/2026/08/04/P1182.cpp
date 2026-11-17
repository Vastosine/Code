#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int n, m, mx = 0;
    cin >> n >> m;
    vector<int> a(n);
    for (int &i : a) cin >> i, mx = std::max(mx, i);
    int l = mx - 1, r = 1e9 + 1;
    if (n == m) return cout << mx, 0;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        int ans = 1, sum = 0;
        for (int i : a) {
            if (sum + i > mid) sum = 0, ans++;
            sum += i;
        }
        if (ans <= m) r = mid;
        else l = mid;
    }
    cout << r;
}