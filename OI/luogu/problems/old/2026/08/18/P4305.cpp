// Problem : P4305 [JLOI2011] 不重复数字 https://www.luogu.com.cn/problem/P4305
// Time    : 2026-08-18 11:26:09

#include <iostream>
#include <unordered_set>
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
    std::unordered_set<int> s;
    while (n--) {
        int x;
        cin >> x;
        if (s.find(x) == s.end()) {
            s.insert(x);
            cout << x << " ";
        }
    }
    cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}