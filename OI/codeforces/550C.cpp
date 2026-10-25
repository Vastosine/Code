// Problem : C. Divisibility by Eight https://codeforces.com/problemset/problem/550/C
// Time    : 2026-10-25 19:13:46
#include <iostream>
#include <string>
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
    string s;
    cin >> s;
    int n = (int) s.length();
    vector<vi> f(n, vi(2, -1));
    for (int i = n - 1; ~i; i--) {
        int x = s[i] - '0';
        if (x % 2 == 0) {
            f[i][0] = x;
            if (x % 8 == 0) return (string)"YES\n" + s[i];
        }
        for (int j = i + 1; j < n; j++) {
            int y;
            if (~f[j][0] && (y = x * 10 + f[j][0]) % 4 == 0) {
                if (y % 8 == 0) return "YES\n" + to_string(y);
                else f[i][1] = y;
            }
            if (~f[j][1] && (y = x * 100 + f[j][1]) % 8 == 0) return "YES\n" + to_string(y);
        }
    }
    return (string)"NO";
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