// Problem : P2822 [NOIP 2016 提高组] 组合数问题 https://www.luogu.com.cn/problem/P2822
// Time    : 2026-08-19 08:59:43

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int k;
int c = 1;

void solve() {
    const int maxn = 2e3 + 5;
    vector<vi> f(maxn, vi(maxn));
    vector<vi> a(maxn, vi(maxn));
    f[0][0] = 1;
    a[0][0] = !(f[0][0] % k);
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            f[i][j] = !j ? 1 : (f[i - 1][j] + f[i - 1][j - 1]) % k;
            a[i][j] = a[i - 1][j] + (j ? (a[i][j - 1] - a[i - 1][j - 1]) : 0) + (!(f[i][j] % k) && j <= i);
            // cout << a[i][j] << " ";
        }
        // cout << "\n";
    }
    while (c--) {
        int n, m;
        cin >> n >> m;
        cout << a[n][m] << "\n";
    }
}

int main() {
    cin >> c >> k;
    solve();
    return 0;
}