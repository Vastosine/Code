// Problem : C. Yet Another Black Cell Problem https://codeforces.com/contest/2272/problem/C
// Time    : 2026-10-26 22:36:09
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

bool check(const vi &dis, int k, int m) {
    vi p;
    for (int d : dis) {
        p.push_back(d / k + (d % k > 0) - 1);
    }
    if (p.size() == 1) return p[0] <= m;
    vi f(p.size());
    f[0] = p[0];
    f[1] = p[1] + p[0];
    for (int i = 2; i < (int) f.size(); i++) {
        f[i] = min(f[i - 1], f[i - 2]) + p[i];
    }
    return f.back() <= m;
}

auto solve() {
    int n, m;
    cin >> n >> m;
    vi a(n), b;
    cin >> a;
    // Sort(a);
    for (int i = 1; i < n; i++) b.push_back(a[i] - a[i - 1]);
    int l = 0, r = a.back();
    while (l < r - 1) {
        int x = (l + r) >> 1;
        if (check(b, x, m)) r = x;
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