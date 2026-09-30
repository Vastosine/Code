// Problem : B. Delete and Concatenate https://codeforces.com/contest/2245/problem/B
// Time    : 2026-09-30 09:57:49
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
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    for (int &i : a) i -= m;
    vector<vi> b(2);
    for (int i = 0; i < n; i++) b[i % 2].push_back(a[i]);
    sort(b[0]);
    sort(b[1]);
    vi l(2, 0), r(2);
    r[0] = b[0].size() - 1, r[1] = b[1].size() - 1;
    b[0].push_back(0);
    b[1].push_back(0);
    int ans = 0;
    while (l[0] <= r[0] || l[1] <= r[1]) {
        int k = l[1] <= r[1] && (l[0] > r[0] || b[1][r[1]] > b[0][r[0]]);
        if (l[!k] <= r[!k] && b[!k][l[!k]] > 0) ans += b[!k][l[!k]];
        ans += b[k][r[k]];
        if (l[!k] <= r[!k]) l[!k]++;
        r[k]--;
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