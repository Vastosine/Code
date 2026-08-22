// Problem : P1469 找筷子 https://www.luogu.com.cn/problem/P1469
// Time    : 2026-08-19 08:59:39

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    while (n--) {
        int x;
        cin >> x;
        ans ^= x;
    }
    cout << ans;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie();
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}