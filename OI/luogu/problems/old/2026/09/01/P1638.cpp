// Problem : P1638 逛画展 https://www.luogu.com.cn/problem/P1638
// Time    : 2026-09-01 17:31:06

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
    vi a(n), vis(m + 1);
    int ept = m, ans = n, x = 0, y = n - 1;
    cin >> a;
    for (int i = 0, j = 0; j <= n; i++) {
        while (ept && j < n) ept -= !vis[a[j++]]++;
        if (ept) break;
        if (j - i < ans) {
            x = i;
            y = j - 1;
            ans = j - i;
        }
        ept += !--vis[a[i]];
    }
    cout << x + 1 << " " << y + 1;
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