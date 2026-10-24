// Problem : E. Anfisa the Monkey https://codeforces.com/problemset/problem/44/E
// Time    : 2026-10-24 12:25:56
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
    int k, l, r;
    string s;
    cin >> k >> l >> r >> s;
    int n = (int) s.length();
    vector<vi> f(n + 1, vi(k + 1, -1));
    f[0][0] = 0;
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            for (int t = l; t <= r && t <= i; t++) {
                if (~f[i - t][j - 1]) f[i][j] = i - t;
            }
        }
    }
    if (!~f[n][k]) {
        cout << "No solution\n";
    } else {
        vector<string> ans(k);
        for (int i = n, j = k; i && j; i = f[i][j--]) {
            ans[j - 1] = s.substr(f[i][j], i - f[i][j]);
        }
        for (auto &t : ans) cout << t << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}