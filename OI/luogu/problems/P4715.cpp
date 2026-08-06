// Problem : P4715 【深基16.例1】淘汰赛 https://www.luogu.com.cn/problem/P4715
// Time    : 2026-08-05 20:14:22

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n;
    cin >> n;
    vector<int> a(1 << n), b(1 << n);
    cin >> a;
    for (int i = 0; i < (1 << n); i++) b[i] = i;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << (n - i + 1)); j += 2) {
            b[j / 2] = b[j + (a[b[j]] < a[b[j + 1]])];
            // cout << b[j / 2];
        }
    }
    cout << b[a[b[0]] > a[b[1]]] + 1;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}