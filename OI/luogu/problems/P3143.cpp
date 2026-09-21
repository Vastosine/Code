// Problem : P3143 [USACO16OPEN] Diamond Collector S https://www.luogu.com.cn/problem/P3143
// Time    : 2026-09-01 17:31:17

#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

int abs(int x) {
    return x < 0 ? -x : x;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    sort(a);
    int ans = 0;
    for (int l = 0, r = 0; r < n; r++) {
        while (a[r] - a[l] > 2 * k + 1) l++;
        ans = std::max(ans, r - l + 1);
    }
    int x = 0, y = 0, l0, r0;
    for (int l = 0, r = 0; r < n; r++) {
        while (a[r] - a[l] > k) l++;
        if (r - l)
    }
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