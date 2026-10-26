// Problem : E. Memory Cell Interception https://codeforces.com/contest/2272/problem/E
// Time    : 2026-10-26 22:36:11
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
    vi n(2);
    vector<vi> b(2), ans(2);
    vector<string> a(2);
    cin >> n >> a;
    for (int i = 0; i < 2; i++) {
        b[i].assign(n[i], 0);
        for (int j = 0; j < n[i]; j++) {
            b[i][j] = a[i][j] == 'W';
        }
        for (int j = n[i] - 2; ~j; j--) {
            b[i][j] += b[i][j + 1];
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0, pre = -1; j < n[i]; j++) {
            if (a[i][j] == 'W') {
                pre = j;
                continue;
            }
            if (pre == -1) {
                ans[i].push_back(b[!i][0] + 1);
            } else {
                int id = n[!i] - (j - pre) + 1;
                if (id < 0) id = 0;
                ans[i].push_back(1 + n[!i] + (id < n[!i] ? b[!i][id] : 0));
            }
        }
        cout << ans[i] << "\n";
    }
    return 0LL;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}