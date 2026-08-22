// Problem : P1835 素数密度 https://www.luogu.com.cn/problem/P1835
// Time    : 2026-08-19 08:59:50

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

#define int long long

void solve() {
    int l, r;
    cin >> l >> r;
    if (l == 1) l = 2;
    vector<int> is(r - l + 1, 1);
    for (int i = 2; i * i <= r; i++) {
        for (int j = std::max(l / i * i, i * 2); j <= r; j += i) {
            if (j >= l) is[j - l] = false;
        }
    }
    int ans = 0;
    for (int i : is) ans += i;
    cout << ans;
}

signed main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}