// Problem : C. Floor and Mod https://codeforces.com/problemset/problem/1485/C
// Time    : 2026-10-31 10:34:49
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

ll Main([[maybe_unused]] int C = 0) {
    ll x, y;
    cin >> x >> y;
    if (x < 3 || y < 2) return 0;
    if (x >= y * y - 1) return (y - 1) * y / 2;
    ll y0 = sqrt(x + 1);
    ll ans = (y0 - 1) * y0 / 2;
    for (int i = y0 + 2; i <= y + 1 && i <= x; ) {
        ll t = x / i;
        ll nxt = min(y + 1, x / t);
        ans += (nxt - i + 1) * t;
        i = nxt + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
