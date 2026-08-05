// Problem : P4387 【深基15.习9】验证栈序列 https://www.luogu.com.cn/problem/P4387
// Time    : 2026-08-05 18:40:24

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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;
    std::stack<int> st;
    int t = 0;
    for (int i : b) {
        while (st.empty() || st.top() != i) {
            if (t == n) return cout << "No\n", void();
            st.push(a[t++]);
        }
        st.pop();
    }
    cout << "Yes\n";
}

int main() {
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}