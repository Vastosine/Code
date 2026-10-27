// Problem : C. Another Problem on Strings https://codeforces.com/problemset/problem/165/C
// Time    : 2026-10-27 09:43:48
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
    int n, len;
    string s;
    cin >> n >> s;
    len = (int) s.length();
    vector<ll> a;
    for (int i = 0, c = 0; i <= len; i++) {
        if (i == len || s[i] == '1') a.push_back(c), c = 0;
        else c++;
    }
    ll ans = 0;
    int m = (int) a.size();
    for (int i = 0; i + n < m; i++) {
        if (n) ans += (a[i] + 1) * (a[i + n] + 1);
        else ans += a[i] * (a[i] + 1) / 2;
    }
    return ans; 
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