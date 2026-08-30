// Problem : P2660 zzc 种田 https://www.luogu.com.cn/problem/P2660
// Time    : 2026-08-30 10:40:24

#include <iostream>
#include <vector>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int f(int x, int y) {
    if (x < y) return f(y, x);
    if (y == 0) return 0;
    int z = x / y;
    return y * 4 * z + f(y, x % y);
}

void solve() {
    int a, b;
    cin >> a >> b;
    cout << f(a, b);
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}