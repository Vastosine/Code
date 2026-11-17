// Problem : P1143 进制转换 https://www.luogu.com.cn/problem/P1143
// Time    : 2026-08-19 08:59:38

#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n, m;
    cin >> n;
    std::string s;
    cin >> s;
    int ans = 0;
    for (int i : s) {
        int x = i >= 'A' ? i - 'A' + 10 : i - '0';
        ans = ans * n + x;
    }
    std::stack<int> st;
    cin >> m;
    while (ans) {
        st.push(ans % m);
        ans /= m;
    }
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        if (x >= 10) cout << char(x - 10 + 'A');
        else cout << char(x + '0');
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}