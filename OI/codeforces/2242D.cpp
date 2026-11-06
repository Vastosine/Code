// Problem : D. Two Digit Strings https://codeforces.com/problemset/problem/2242/D
// Time    : 2026-11-06 11:07:17
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    string s[2];
    cin >> s[0] >> s[1];
    int n[2] = {(int) s[0].size(), (int) s[1].size()};
    vector<vi> a(2), f(n[0] + 1, vi(n[1] + 1));
    for (int i = 0; i < 2; i++) {
        a[i].assign(n[i] + 1, 0);
        a[i][0] = 0;
        for (int j = 0; j < n[i]; j++) {
            a[i][j + 1] = (a[i][j] + s[i][j] - '0') % 10;
        }
    }
    if (a[0].back() != a[1].back()) return -1;
    for (int i = 1; i <= n[0]; i++) {
        for (int j = 1; j <= n[1]; j++) {
            f[i][j] = max(f[i - 1][j], max(f[i][j - 1], f[i - 1][j - 1] + (a[0][i] == a[1][j])));
        }
    }
    return f[n[0]][n[1]];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */