#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
#define int long long

const int PRECISION = 1;
const int N = 60 * 60 * 12 * PRECISION;

int available(int a, int b, int c) {
    a %= N, b %= N, c %= N;
    int s[4] = {a, b, c};
    std::sort(s, s + 3);
    s[3] = s[0] + N;
    int ans = N;
    for (int i = 0; i < 3; i++) {
        ans = std::min(ans, s[i + 1] - s[i]);
    }
    return (ans - 1) / 120 / PRECISION;
}

signed main() {
    int d;
    vector<int> ans(121);
    int second = 0, minute = 0, hour = 0;
    for (int i = 0; i < N; i++) {
        hour += 1;
        minute += 12;
        second += 12 * 60;
        int x = available(second, minute, hour);
        if (x >= 0) ans[x]++;
    }
    for (int i = 120; i; i--) {
        ans[i - 1] += ans[i];
    }
    while (cin >> d && ~d) {
        cout << std::fixed << std::setprecision(0) << std::setfill('0') << std::setw(0) << ans[d] * 100 / N << "." << std::setw(3) << ans[d] * 1000000 / N % 10000 * 1.0 / 10 << "\n";
    }
}