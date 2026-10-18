// Problem : G. The 67th Iteration of \"Counting is Fun\" https://codeforces.com/contest/2218/problem/G
// Time    : 2026-10-08 09:41:39
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

const int M = 676767677;

int solve() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    int ans = 1;
    vector<vi> c(m);
    for (int i = 0; i < n; i++) {
        if (a[i] && !((i && a[i] > a[i - 1]) || (i < n - 1 && a[i] > a[i + 1]))) return 0;
        c[a[i]].push_back(i);
    }
    for (int i = 1, s = c[0].size(); i < m; s += c[i].size(), i++) {
        for (int j : c[i]) {
            ans *= (!j || a[j] - a[j - 1] <= 1) && (j >= n - 1 || a[j] - a[j + 1] <= 1) ? s : c[i - 1].size();
            ans %= M;
        }
    }
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