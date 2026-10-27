// Problem : B. Cinema Cashier https://codeforces.com/problemset/problem/10/B
// Time    : 2026-10-27 08:47:30
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
    vector<vi> a(m, vi(m));
    while (n--) {
        int s;
        cin >> s;
        int ans = 1 << 30, x, y;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j + s <= m; j++) {
                int t = 0;
                for (int k = 0; k < s; k++) {
                    if (a[i][j + k]) {
                        t = 1 << 30;
                        break;
                    }
                    t += abs(i - m / 2) + abs(j + k - m / 2);
                }
                if (t < ans) {
                    ans = t;
                    x = i;
                    y = j;
                }
            }
        }
        if (ans == 1 << 30) cout << "-1\n";
        else {
            cout << x + 1 << " " << y + 1 << " " << y + s << "\n";
            for (int i = 0; i < s; i++) a[x][y + i] = 1;
        }
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