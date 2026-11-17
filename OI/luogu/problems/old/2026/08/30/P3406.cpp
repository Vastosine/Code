// Problem : P3406 海底高铁 https://www.luogu.com.cn/problem/P3406
// Time    : 2026-08-30 13:03:16

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

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1), p(m);
    cin >> p;
    for (int i = 1; i < m; i++) {
        int u = p[i], v = p[i - 1];
        if (u > v) std::swap(u, v);
        a[u]++;
        a[v]--;
    }
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int x, y, z, w = a[i];
        cin >> x >> y >> z;
        ans += std::min(x * w, y * w + z);
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