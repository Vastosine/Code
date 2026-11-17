// Problem : P5250 【深基17.例5】木材仓库 https://www.luogu.com.cn/problem/P5250
// Time    : 2026-08-18 11:26:01

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
    int n;
    cin >> n;
    std::set<int> s;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            if (s.find(x) != s.end()) cout << "Already Exist\n";
            else s.insert(x);
        }
        else {
            if (s.empty()) {
                cout << "Empty\n";
                continue;
            }
            auto it = s.lower_bound(x);
            auto pre = it;
            pre--;
            if (it == s.begin()) cout << *it << "\n", s.erase(it);
            else if (it == s.end() || abs(*it - x) >= abs(*pre - x)) cout << *pre << "\n", s.erase(pre);
            else cout << *it << "\n", s.erase(it);
            
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}