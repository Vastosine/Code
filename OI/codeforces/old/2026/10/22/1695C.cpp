// Problem : C. Zero Path https://codeforces.com/problemset/problem/1695/C
// Time    : 2026-10-22 14:35:23
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

void f(pii &s, int x) {
    s.first += x;
    s.second += x;
}

void f(pii &s, const pii &t) {
    s.first = min(s.first, t.first);
    s.second = max(s.second, t.second);
}

auto solve() {
    int n, m;
    cin >> n >> m;
    vector<vi> a(n, vi(m));
    cin >> a;
    if (!((n + m) & 1)) return false;
    vector<pii> s(m, {n + m, -n - m});
    s[0] = {0, 0};
    for (int i = 0; i < n; i++) {
        f(s[0], a[i][0]);
        for (int j = 1; j < m; j++) {
            f(s[j], s[j - 1]);
            f(s[j], a[i][j]);
        }
    }
    return s.back().first <= 0 && s.back().second >= 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    // while (c--) solve();
    const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}