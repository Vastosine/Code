// Problem : P1403 [AHOI2005] 约数研究 https://www.luogu.com.cn/problem/P1403
// Time    : 2026-08-30 10:40:25

#include <iostream>
#include <vector>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n;
    cin >> n;
    vi a(n + 1, 1);
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] == 1) {
            for (int j = i * 2; j <= n; j += i) {
                int y = j, c = 0;
                while (y % i == 0) y /= i, c++;
                a[j] *= c + 1;
            } 
            a[i]++;
        }
        ans += a[i];
    }
    cout << ans;
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}