// Problem : E1. Three Blocks Palindrome (easy version) https://codeforces.com/problemset/problem/1335/E1
// Time    : 2026-10-27 15:37:55
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
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    vector<vi> c(n + 1, vi(26));
    for (int i = 1; i <= n; i++) {
        c[i] = c[i - 1];
        c[i][a[i - 1] - 1]++;
    }
    int ans = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int p = 0, q = 0;
            for (int k = 0; k < 26; k++) {
                p = max(p, 2 * min(c[l - 1][k], c[n][k] - c[r][k]));
                q = max(q, c[r][k] - c[l - 1][k]);
            }
            ans = max(ans, p + q);
        }
    }
    return ans;
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