// Problem : P5076 【深基16.例7】普通二叉树（简化版） https://www.luogu.com.cn/problem/P5076
// Time    : 2026-08-05 20:14:25

#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    std::set<int> a;
    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
            case 1: {
                // a.count()
            }
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}