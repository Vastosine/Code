// Problem : C. Sum of Distinct Values in a Matrix https://codeforces.com/problemset/problem/2253/C
// Time    : 2026-10-09 10:51:00
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
    int n, m, x, y, s;
    cin >> n >> m >> x >> y;
    s = n + m - 1;
    vector<vi> a = {vi(x), vi(y)}, b(3);
    vi c;
    cin >> a;
    sort(a[0]);
    sort(a[1]);
    while (c.size() < s && (a[0].size() || a[1].size())) {
        int p = a[0].empty() ? -1 : a[0].back(), q = a[1].empty() ? -1 : a[1].back();
        int k = p == q ? 2 : (b[1].size() < m && (q > p || b[0].size() == n));
        if (a[k].empty()) break;
        int t = a[k > 0].back();
        b[k].push_back(t);
        c.push_back(t);
        for (int i = 0; i < 2; i++) while (!a[i].empty() && a[i].back() == t) a[i].pop_back();
    }
    int ans = 0;
    for (int i : c) ans += i;
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}