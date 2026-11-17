// Problem : P1918 保龄球 https://www.luogu.com.cn/problem/P1918
// Time    : 2026-08-18 11:26:04

#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    std::map<int, int> a;
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = i;
    }
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        auto it = a.find(x);
        cout << (it == a.end() ? 0 : it->second) << "\n";
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}