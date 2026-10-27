// Problem : C. Palindrome Basis https://codeforces.com/problemset/problem/1673/C
// Time    : 2026-10-27 09:07:21
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

vector<ll> is, lst, f;
const int M = 1e9 + 7;

void init(int n) {
    is.assign(n, 1);
    for (int i = 0; i < n; i++) {
        string s = to_string(i);
        int len = (int) s.length();
        for (int j = 0; j * 2 < len; j++) {
            is[i] &= s[j] == s[len - j - 1];
        }
        if (is[i]) lst.push_back(i);
    }
    int m = lst.size();
    f.assign(n, 0);
    f[0] = 1;
    for (int j = 1; j < m; j++) {
        for (int i = 1; i < n; i++) {
            if (lst[j] <= i) f[i] = (f[i] + f[i - lst[j]]) % M;
            // for (int k = 0; k <= j; k++) {
            //     f[i][j] += f[i - lst[j]][k];
            // }
        }
    }
}

auto solve() {
    int n;
    cin >> n;
    return f[n];
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    init(4e4 + 10);
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}