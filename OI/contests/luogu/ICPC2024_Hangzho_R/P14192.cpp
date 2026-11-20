// Problem : P14192 [ICPC 2024 Hangzhou R] Fuzzy Ranking https://www.luogu.com.cn/problem/P14192?contestId=281894
// Time    : 2026-09-20 17:30:23

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

}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}