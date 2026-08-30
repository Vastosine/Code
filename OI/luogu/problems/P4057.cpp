// Problem : P4057 [Code+#1] 晨跑 https://www.luogu.com.cn/problem/P4057
// Time    : 2026-08-29 11:10:08

#include <iostream>
#include <numeric>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    long long x, y, z;
    cin >> x >> y >> z;
    cout << std::lcm(x, std::lcm(y, z));
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}