// Problem : P5266 【深基17.例6】学籍管理 https://www.luogu.com.cn/problem/P5266
// Time    : 2026-08-18 11:26:02

#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::string;

void solve() {
    int q;
    cin >> q;
    std::map<string, int> a;
    while (q--) {
        int op, x;
        string name;
        cin >> op;
        if (op == 4) {
            cout << a.size() << "\n";
        } else {
            cin >> name;
            if (op == 1) {
                cin >> x;
                a[name] = x;
                cout << "OK\n";
            } else {
                auto it = a.find(name);
                if (it == a.end()) {
                    cout << "Not found\n";
                    continue;
                }
                if (op == 2) {
                    cout << it->second << "\n";
                } else {
                    a.erase(it);
                    cout << "Deleted successfully\n";
                }
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