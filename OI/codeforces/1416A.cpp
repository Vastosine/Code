// Problem : A. k-Amazing Numbers https://codeforces.com/problemset/problem/1416/A
// Time    : 2026-10-23 22:58:31
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
    vi oc(n + 1, -1), sp(n + 1);
    for (int i = 0; i < n; i++) {
        sp[a[i]] = max(sp[a[i]], i - oc[a[i]]);
        oc[a[i]] = i;
    } 
    for (int i = 1; i <= n; i++) sp[i] = max(sp[i], n - oc[i]);
    vi ans(n, -1);
    for (int i = n, p = 1; i; i--) {
        while (p <= n && sp[p] > i) p++;
        if (p > n) break;
        ans[i - 1] = p;
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