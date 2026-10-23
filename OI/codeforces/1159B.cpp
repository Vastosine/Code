// Problem : B. Expansion coefficient of the array https://codeforces.com/problemset/problem/1159/B
// Time    : 2026-10-23 13:05:42
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll NEG = -(1LL << 60); [[maybe_unused]] const ll INF = (1LL << 60);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int ans = 0x7fffffff;
    for (int i = 0; i < n; i++) {
        if (i) ans = min(ans, a[i] / i);
        if (i < n - 1) ans = min(ans, a[i] / (n - 1 - i));
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}