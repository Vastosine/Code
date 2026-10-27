// Problem : F. Pizza Delivery https://codeforces.com/problemset/problem/2193/F
// Time    : 2026-10-27 16:03:15
#include <iostream>
#include <utility>
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
    int n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;
    vector<pii> p(n);
    for (auto &[u, v] : p) cin >> u;
    for (auto &[u, v] : p) cin >> v;
    Sort(p);
    vector<vector<ll>> a;
    a.push_back({ax, ay, ay});
    for (auto &[u, v] : p) {
        if (a.back()[0] != u) a.push_back({u, v, v});
        else a.back()[2] = v;
    }
    a.push_back({bx, by, by});
    int m = (int) a.size();
    vector<pair<ll, ll>> f(m);
    for (int i = 1; i < m; i++) {
        auto &[u, v] =f[i - 1];
        f[i] = {
            a[i][0] - a[i - 1][0] + a[i][2] - a[i][1] + 
            min(u + abs(a[i][1] - a[i - 1][2]), v + abs(a[i][1] - a[i - 1][1])),
            a[i][0] - a[i - 1][0] + a[i][2] - a[i][1] + 
            min(u + abs(a[i][2] - a[i - 1][2]), v + abs(a[i][2] - a[i - 1][1]))
        };
    }
    return f.back().first;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}