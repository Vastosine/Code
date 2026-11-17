// Problem : P3397 地毯 https://www.luogu.com.cn/problem/P3397
// Time    : 2026-08-30 12:06:08

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
    int n, m;
    cin >> n >> m;
    vector<vi> a(n + 2, vi(n + 2));
    while (m--) {
        int p, q, x, y;
        cin >> p >> q >> x >> y;
        x++, y++;
        a[p][q]++;
        a[p][y]--;
        a[x][q]--;
        a[x][y]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            cout << a[i][j] << " ";
        }
        cout << "\n";
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