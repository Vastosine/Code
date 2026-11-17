// Problem : P3913 车的攻击 https://www.luogu.com.cn/problem/P3913
// Time    : 2026-08-19 08:59:45

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
    long long n, k;
    cin >> n >> k;
    long long x, y;
    vi X(k), Y(k);
    for (int i = 0; i < k; i++) {
        cin >> X[i] >> Y[i];
    }
    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());
    x = y = n - 1;
    for (int i = 1; i < k; i++) {
        x -= X[i] != X[i - 1];
        y -= Y[i] != Y[i - 1];
    }
    cout << n * n - x * y;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}