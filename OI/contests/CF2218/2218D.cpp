// Problem : D. The 67th OEIS Problem https://codeforces.com/contest/2218/problem/D
// Time    : 2026-10-08 09:41:36
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

vi ans;

auto solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}

void init() {
    vi vis(1e4, 0), a;
    for (int i = 1; i <= 1e4; i += 2) {
        if (i * i < 1e4) vis[i * i] = 1;
        if (vis[i] && i > 1) continue;
        a.push_back(i);
    }
    for (int i = 0; i < a.size() - 1 && ans.size() < 1e4 + 1; i++) {
        int x = a[i], y = 1e17 / a[i + 1], j;
        for (j = x * x; j < y; j *= 2) {
            ans.push_back(j);
        }
        ans.push_back(j * a[i + 1]);
    }
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    init();
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}