// Problem : F. The 67th Tree Problem https://codeforces.com/contest/2218/problem/F
// Time    : 2026-10-08 09:41:38
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
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

auto solve() {
    int x, y;
    cin >> x >> y;
    if (x > y || (!x && y % 2 == 0)) return cout << "NO\n", void();
    int n = x + y;
    (n % 2 ? y : x)--;
    y -= x;
    int c = 1;
    vector<pii> ans;
    for (int i = 0; i < y; i++) {
        ans.push_back({1, ++c});
    }
    for (int i = 0; i < 2 * x; i++) {
        ans.push_back({c, c + 1});
        c++;
    }
    cout << "YES\n";
    for (auto &[u, v] : ans) cout << u << " " << v << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}