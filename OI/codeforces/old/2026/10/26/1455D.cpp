// Problem : D. Sequence and Swaps https://codeforces.com/problemset/problem/1455/D
// Time    : 2026-10-26 15:45:45
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
    int n, x;
    cin >> n >> x;
    vi a(n), b(n), f(n, 1);
    cin >> a;
    b.back() = a.back();
    for (int i = n - 2; ~i; i--) b[i] = min(b[i + 1], a[i]);
    int ans = 0;
    for (int i = 0, c = 0; i < n - 1; i++) {
        if (a[i] > x && (!i || a[i] != a[i - 1])) {
            c++;
        }
        if (a[i] > b[i]) {
            if (x > b[i]) return -1;
            ans += c;
            x = a[i];
            c = 0;
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