// Problem : P8218 【深进1.例1】求区间和 https://www.luogu.com.cn/problem/P8218
// Time    : 2026-08-30 11:52:45

#include <iostream>
#include <vector>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n, q;
    cin >> n;
    vi a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = b[i - 1] + a[i];
    }
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << b[r] - b[l - 1] << "\n";
    }
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}