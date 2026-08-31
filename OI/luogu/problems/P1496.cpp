// Problem : P1496 火烧赤壁 https://www.luogu.com.cn/problem/P1496
// Time    : 2026-08-30 13:03:12

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
    int n;
    cin >> n;
    vector<vi> a(n, vi(2));
    cin >> a;
    sort(a);
    vi p;
    int ans = 0;
    for (const vi &i : a) {
        if (p.empty()) p = i;
        else if (p[1] >= i[0]) p[1] = std::max(i[1], p[1]);
        else {
            ans += p[1] - p[0];
            p = i;
        }
    }
    cout << ans + p[1] - p[0];
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