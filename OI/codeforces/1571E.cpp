// Problem : E. Fix the String https://codeforces.com/problemset/problem/1571/E
// Time    : 2026-10-28 10:06:11
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
    string s, t;
    cin >> s >> t;
    int ans = 0;
    for (int i = 0; i + 3 < n; i++) {
        if (t[i] == '0') continue;
        if (s[i] == ')') ans++, s[i] = '(';
        if (s[i + 3] == '(') ans++, s[i + 3] = ')';
        if (s[i + 1] == s[i + 2]) ans++, s[i + 1] = ')', s[i + 2] = '(';
        if (i && t[i - 1] == '1') return -1;
        if (i > 2 && t[i - 3] == '1') return -1;
        if (i > 1 && t[i - 2] == '1' && s[i - 1] == '(') ans++, s[i - 1] = ')'; 
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