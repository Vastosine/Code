// Problem : D. Falling Concrete https://codeforces.com/contest/2266/problem/D
// Time    : 2026-09-21 22:37:13

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
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    for (int i = 0; i < n; i++) {
        a[i] -= i;
    }
    sort(a);
    int ans = 1;
    int i, j;
    for (i = 1, j = 1; i < n; i++) {
        if (a[i] == a[i - 1] + 1) j++;
        else if (a[i] != a[i - 1]) ans = std::max(j, ans), j = 1;
    }
    ans = std::max(j, ans);
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}