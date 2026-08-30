// Problem : P2651 添加括号III https://www.luogu.com.cn/problem/P2651
// Time    : 2026-08-29 11:10:10

#include <iostream>
#include <numeric>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

bool solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    if (a.size() <= 1) return true;
    int ans = a[1];
    for (int i = 0; i < n; i++) {
        if (i == 1) continue;
        ans /= std::gcd(ans, a[i]);
    }
    return ans == 1;
}

int main() {
    int c = 1;
    cin >> c;
    const char out[2][10] = {"No", "Yes"};
    while (c--) cout << out[solve()] << "\n";
    return 0;
}