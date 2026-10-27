// Problem : E. The Humanoid https://codeforces.com/problemset/problem/1759/E
// Time    : 2026-10-26 12:52:37
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
    int n, h;
    cin >> n >> h;
    vi a(n);
    cin >> a;
    Sort(a);
    ll ans = 0;
    for (int k = 0; k < 3; k++) {
        ll s = h, m = 0, i;
        for (i = 0; i < n; i++) {
            int x = a[i];
            while (m < 3 && x >= s) {
                if (k == m) s *= 3;
                else s *= 2;
                m++;
            }
            if (x >= s) break; 
            s += x / 2;
        }
        ans = max(ans, i);
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