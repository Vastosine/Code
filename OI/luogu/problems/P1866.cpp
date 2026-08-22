// Problem : P1866 编号 https://www.luogu.com.cn/problem/P1866
// Time    : 2026-08-19 08:59:42

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    const int M = 1e9 + 7;
    int n;
    cin >> n;
    long long ans = 1;
    vi a(n);
    cin >> a;
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        if (i >= a[i]) return cout << 0, void();
        ans = ans * (a[i] - i) % M;
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}