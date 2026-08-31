// Problem : P1083 [NOIP 2012 提高组] 借教室 https://www.luogu.com.cn/problem/P1083
// Time    : 2026-08-30 13:03:17

#include <iostream>
#include <vector>
#include <algorithm>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 2), b, p, q;
    b = p = q = vi(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = n; i; i--) {
        a[i] -= a[i - 1];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i] >> p[i] >> q[i];
    }
    int id = 0, l = 0, r = m + 1;
    while (r - l > 1) {
        int w = (l + r) / 2;
        int k = w > id ? 1 : -1;
        while (id != w) {
            if (w > id) id++;
            a[p[id]] -= k * b[id];
            a[q[id] + 1] += k * b[id];
            if (w < id) id--;
        }
        int y = 0;
        bool ans = true;
        for (int i = 1; i <= n; i++) {
            y += a[i];
            if (y < 0) {
                ans = false;
                break;
            }
        }
        if (ans) l = w;
        else r = w;
    }
    if (r == m + 1) cout << 0;
    else cout << "-1\n" << r;
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