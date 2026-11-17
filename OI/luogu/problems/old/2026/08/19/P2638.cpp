// Problem : P2638 安全系统 https://www.luogu.com.cn/problem/P2638
// Time    : 2026-08-19 08:59:46

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

#define int __int128
typedef vector<int> vi;
vector<vector<vi>> dp;

int f(int n, int a, int b) {
    if (dp[n][a][b]) return dp[n][a][b];
    if (!n) return 1;
    int ans = 0;
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            ans += f(n - 1, a - i, b - j);
        }
    }
    return dp[n][a][b] = ans;
}

void print(int x) {
    if (!x) return;
    print(x / 10);
    cout << char(x % 10 + '0');
}

void solve() {
    long n, a, b;
    cin >> n >> a >> b;
    dp.assign(n + 1, vector<vi>(a + 1, vi(b + 1)));
    print(f(n, a, b));
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}