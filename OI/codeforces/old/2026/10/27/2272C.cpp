// Problem : C. Yet Another Black Cell Problem https://codeforces.com/contest/2272/problem/C
// Time    : 2026-10-27 08:08:14
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

bool check(const vi &a, int k, int m) {
    vi p;
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        if ((i && a[i] - a[i - 1] <= k) || (i < n - 1 && a[i + 1] - a[i] <= k)) continue;
        p.push_back(i);
    }
    int ans = 0, pn = (int) p.size();
    for (int i = 0; i < pn; i++) {
        ans++;
        if (i < pn - 1 && a[p[i + 1]] - a[p[i]] <= 2 * k) i++;
    }
    return ans <= m;
}

auto solve() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    int l = 0, r = a.back();
    while (l < r - 1) {
        int x = (l + r) >> 1;
        if (check(a, x, m)) r = x;
        else l = x;
    }
    return r;
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