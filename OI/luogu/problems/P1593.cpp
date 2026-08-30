// Problem : P1593 因子和 https://www.luogu.com.cn/problem/P1593
// Time    : 2026-08-30 10:40:26

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

const int M = 9901;

int pow(int x, int n) {
    return n ? pow(x * x % M, n / 2) * (n % 2 ? x : 1) % M : 1;
}

int sum(int p, int n) {
    if (!n) return 1;
    int m = (n - 1) / 2;
    int x = sum(p, m);
    int r = pow(p, m + 1);
    return (x + x * r + !(n % 2) * r * r) % M;
}

void solve() {
    int a, b;
    cin >> a >> b;
    int ans = 1;
    for (int i = 2; i <= a; i++) {
        int n = 0;
        while (a % i == 0) a /= i, n++;
        ans = (ans * sum(i, n * b % (M - 1))) % M;
    }
    cout << ans;
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    std::cerr << clock() << "\n";
    return 0;
}