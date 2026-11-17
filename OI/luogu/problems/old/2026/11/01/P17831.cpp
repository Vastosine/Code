// Problem : P17831 [CSP-S 2026] 能量水晶 / crystal（民间数据） https://www.luogu.com.cn/problem/P17831?contestId=369912
// Time    : 2026-11-01 19:44:30
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

auto Main([[maybe_unused]] int C = 0) {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    cin >> a;
    Sort(a);
    ll ans = 0;
    for (ll l = 0, r = 0, s = 0; l < n; l++) {
        ll dx;
        while (r < n - 1 && s + (dx = (r - l + 1) * (a[r + 1] - a[r])) <= m) r++, s += dx;
        ans = max(ans, r - l + 1);
        s -= a[r] - a[l];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
