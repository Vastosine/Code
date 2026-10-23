// Problem : D. Kefa and Dishes https://codeforces.com/problemset/problem/580/D
// Time    : 2026-10-22 15:06:03
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
inline int popcnt(int x) { return __builtin_popcountll(x); }

auto solve() {
    int n, m, K;
    cin >> n >> m >> K;
    vi a(n), vis(n);
    vector<vi> b(n, vi(n)), f(1 << n, vi(n, -(1LL << 60)));
    cin >> a;
    while (K--) {
        int x, y, c;
        cin >> x >> y >> c;
        b[x - 1][y - 1] = c;
    }
    for (int i = 0; i < n; i++) {
        f[1 << i][i] = a[i];
    }
    int ans = 0;
    for (int i = 1; i < f.size(); i++) {
        for (int j = 0; j < n; j++) {
            if (f[i][j] > -(1LL << 60)) {
                if (popcnt(i) < m) {
                    for (int k = 0; k < n; k++) {
                        if (!((1 << k) & i)) 
                            f[i ^ (1 << k)][k] = max(f[i ^ (1 << k)][k], f[i][j] + b[j][k] + a[k]);
                    }
                }
            }
        }
    }
    for (int i = 1; i < f.size(); i++) {
        if (popcnt(i) == m) ans = 
            max(ans, *max_element(f[i].begin(), f[i].end()));
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}