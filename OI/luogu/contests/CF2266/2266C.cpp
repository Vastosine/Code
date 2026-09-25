// Problem : C. AND, OR, Sort! https://codeforces.com/contest/2266/problem/C
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
    string s;
    cin >> n >> s;
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (s[i - 1] > s[i]) k = 0;
    }
    if (k) return cout << "0\n", void();
    int z = 0;
    for (int i : s) z += i == '0';
    if (s[0] == '1') return cout << z << "\n", void();
    int ans = std::min(z, n - z);
    for (int i = 0, j = 0; i < n; i++) {
        if (j || s[i] != '0') ans = std::min(ans, j + z);
        j += s[i] == '1';
        z -= s[i] == '0';
    }
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