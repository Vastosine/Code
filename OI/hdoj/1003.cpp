#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":\n";
        int n;
        cin >> n;
        vector<int> a(n + 1);
        int min = 0, ans = 0x80000000, ansl, ansr;
        for (int j = 1; j <= n; j++) {
            cin >> a[j];
            a[j] += a[j - 1];
            int x = a[j] - a[min];
            if (x > ans) ans = x, ansl = min + 1, ansr = j;
            if (a[j] < a[min]) min = j;
        }
        cout << ans << " " << ansl << " " << ansr << "\n\n";
    }
}