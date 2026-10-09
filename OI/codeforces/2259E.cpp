// Problem : E. Treasure Map Destruction (Constructive Version) https://codeforces.com/problemset/problem/2259/E
// Time    : 2026-10-09 09:29:26
#include <iostream>
#include <queue>
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

using std::max;
using std::min;

string solve() {
    int n;
    cin >> n;
    vi a(n), l(n, 0), r(n, n), vis(n);
    cin >> a;
    string ans;
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!((i && (a[i] == a[i - 1] + 1 || !~a[i - 1])) || (i < n - 1 && (a[i] == a[i + 1] + 1 || !~a[i + 1])) || a[i] <= 0)) return "-1";
        if (a[i] >= 0) q.push(i), l[i] = r[i] = a[i];
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        q.push(x - 1);
        q.push(x + 1);
        if (x) l[x - 1] = max(l[x - 1], max(l[x] - 1, 0ll)), r[x - 1] = min(r[x - 1], r[x] + 1);
        if (x < n - 1) l[x + 1] = max(l[x + 1], max(l[x] - 1, 0ll)), r[x + 1] = min(r[x + 1], r[x] + 1);
    }
    for (int i = 0; i < n; i++) {
        cout << l[i] << " " << r[i] << "\n";

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