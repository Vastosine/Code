// Problem : P3383 【模板】线性筛素数 https://www.luogu.com.cn/problem/P3383
// Time    : 2026-08-19 08:59:49

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int is[100000000], p[6000000];

void solve() {
    int n, q;
    cin >> n >> q;
    int c = 0;
    for (int i = 2; i * i <= n; i++) {
        if (!is[i]) {
            for (int j = i * 2; j <= n; j += i) {
                is[j] = true;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (!is[i]) p[++c] = i;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << p[x] << "\n";
    }
    // cout << c;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie();
    cout.tie();
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}