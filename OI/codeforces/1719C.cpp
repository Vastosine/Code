// Problem : C. Fighting Tournament https://codeforces.com/problemset/problem/1719/C
// Time    : 2026-10-23 16:13:20
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll NEG = -(1LL << 60); [[maybe_unused]] const ll INF = (1LL << 60);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n), l(n, INF), r(n, INF);
    cin >> a;
    l[0] = 1;
    for (int i = 1, p = 0; i < n; i++) {
        if (a[i] < a[p]) continue;
        r[p] = l[i] = i;
        p = i;
    }
    while (q--) {
        int x, k, ans = 0;
        cin >> x >> k;
        x--;
        if (l[x] < r[x] && k >= l[x]) {
            if (k >= r[x]) ans = r[x] - l[x];
            else ans = k - l[x] + 1;
        }
        cout << ans << "\n";
    }
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