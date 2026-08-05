// Problem : P17200 DKM OI Round 1 - 彩带拼接 https://www.luogu.com.cn/problem/P17200?contestId=344729
// Time    : $data$ 08:12:55

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
#define int long long
void solve() {
    int n, L;
    cin >> n >> L;
    vector<vector<int>> f(2, vector<int>(L + 1, -1)), col(2, vector<int>(L + 1, 0));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int l, v, c;
        cin >> l >> v >> c;
        for (int j = L; j >= l; j--) {
            int p = -1;
            if (~f[0][j - l] && c != col[0][j - l]) p = f[0][j - l];
            else if (~f[1][j - l] && c != col[1][j - l]) p = f[1][j - l];
            if (!~p) continue;
            p += v;
            if (p > f[0][j]) {
                if (col[0][j] != c) {
                    col[1][j] = col[0][j];
                    f[1][j] = f[0][j];
                    col[0][j] = c;
                }
                f[0][j] = p;
            } else if (p > f[1][j] && col[0][j] != c) {
                f[1][j] = p;
                col[1][j] = c;
            }
        }
    }
    cout << f[0][L];
}
#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}