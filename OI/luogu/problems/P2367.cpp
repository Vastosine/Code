// Problem : P2367 语文成绩 https://www.luogu.com.cn/problem/P2367
// Time    : 2026-08-30 12:06:07

#include <iostream>
#include <vector>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i; i--) {
        a[i] -= a[i - 1];
    }
    while (m--) {
        int l, r, x;
        cin >> l >> r >> x;
        a[l] += x;
        if (r < n) a[r + 1] -= x;
    }
    for (int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }
    int ans = a[1];
    for (int i = 2; i <= n; i++) {
        ans = std::min(ans, a[i]);
    }
    cout << ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}