// Problem : P4653 [CEOI 2017] Sure Bet https://www.luogu.com.cn/problem/P4653
// Time    : 2026-09-01 17:31:16

#include <iomanip>
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

bool cmp(double x, double y) { return y < x; }

void solve() {
    int n;
    cin >> n;
    vector<double> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    sort(a, cmp);
    sort(b, cmp);
    double ans = 0;
    double sa = 0, sb = 0;
    for (int i = 0, j = 0; i <= n && j <= n; ) {
        if (sa < sb) sa += a[i++];
        else sb += b[j++];
        ans = std::max(ans, std::min(sa - i - j, sb - i - j));
    }
    cout << std::fixed << std::setprecision(4) << ans;
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