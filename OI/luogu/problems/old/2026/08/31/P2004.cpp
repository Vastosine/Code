// Problem : P2004 领地选择 https://www.luogu.com.cn/problem/P2004
// Time    : 2026-08-30 13:03:15

#include <iostream>
#include <vector>
#include <algorithm>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

void solve() {
    int n, m, c;
    cin >> n >> m >> c;
    vector<vi> a(n + 1, vi(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    int x, y, z = 0x80000000;
    for (int i = 0; i + c <= n; i++) {
        for (int j = 0; j + c <= m; j++) {
            int p = i + c, q = j + c;
            int w = a[p][q] + a[i][j] - a[p][j] - a[i][q];
            if (w > z) x = i, y = j, z = w;
        }
    }
    cout << x + 1 << " " << y + 1;
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