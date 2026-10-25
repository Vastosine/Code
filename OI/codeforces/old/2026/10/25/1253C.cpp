// Problem : C. Sweets Eating https://codeforces.com/problemset/problem/1253/C
// Time    : 2026-10-25 19:33:33
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), f(n);
    cin >> a;
    Sort(a);
    for (int i = 1; i < n; i++) a[i] += a[i - 1];
    for (int i = 0; i < m && i < n; i++) f[i] = a[i];
    for (int i = m; i < n; i++) {
        f[i] = f[i - m] + a[i];
    }
    return f;
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