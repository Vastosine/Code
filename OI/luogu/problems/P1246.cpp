// Problem : P1246 [ECNA 1995] 编码 https://www.luogu.com.cn/problem/P1246
// Time    : 2026-08-19 08:59:47

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::string;
int ans = 0;

int C(int n, int r) {
    int ans = 1;
    for (int i = 0; i < r; i++) {
        ans = ans * (n - i) / (i + 1);
    }
    return ans;
}

void solve() {
    string x;
    cin >> x;
    int n = x.size(), ans = 0;
    for (int i = 1; i < n; i++) {
        ans += C(26, i);
    }
    int d = 0;
    for (int i = 0; i < n; i++) {
        int c = x[i] - 'a';
        if (c < d) return cout << 0, void();
        for (int j = d; j < c; j++) {
            ans += C(26 - j - 1, n - i - 1);
        }
        d = c + 1;
    }
    cout << ans + 1;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}