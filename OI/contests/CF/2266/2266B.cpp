// Problem : B. Three Piles https://codeforces.com/contest/2266/problem/B
// Time    : 2026-09-21 22:37:13

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
    int a, b, c, ans;
    cin >> a >> b >> c;
    cout << std::max(abs(a - b), abs(a + c - b)) << "\n";
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