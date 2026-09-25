// Problem : F. MEX Replacement https://codeforces.com/contest/2266/problem/F
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
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

using std::max;
const int MAX = 1e16;

int solve() {
    int n;
    cin >> n;
    vector<vi> a(n, vi(2));
    cin >> a;
    sort(a, [] (auto x, auto y) { return x > y; });
    int ans = a[0][0];
    if (a.back()[0]) a.push_back({0, 0});
    while (++ans) {
        if (a.size() == 1 && a[0][1] < 1 << (ans - 1)) return ans - 1;
        int r = (1 << (ans - a[0][0] - 1)), s = max(a[0][1] - r, 0ll);
        if (a[0][1] < r) r += r - a[0][1];
        for (int i = 1; i < a.size(); i++) {
            if (r > (MAX >> (a[i - 1][0] - a[i][0] - 1))) return ans - 1;
            r <<= (a[i - 1][0] - a[i][0] - 1);
            if (a[i][1] >= r) s += a[i][1] - r;
            else if (a[i][0]) r += r - a[i][1];
            else if (s + a[i][1] < r) return ans - 1;
        }
    }
    return 0;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}