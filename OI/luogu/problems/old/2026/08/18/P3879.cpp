// Problem : P3879 [TJOI2010] 阅读理解 https://www.luogu.com.cn/problem/P3879
// Time    : 2026-08-18 11:26:10

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
using std::map;

void solve() {
    int n;
    cin >> n;
    vector<map<string, int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        while (m--) {
            string s;
            cin >> s;
            a[i][s]++;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        for (int i = 1; i <= n; i++) {
            if (a[i].find(s) != a[i].end()) cout << i << " ";
        }
        cout << "\n";
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}