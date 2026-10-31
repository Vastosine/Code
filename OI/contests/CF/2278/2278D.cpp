// Problem : D. Lock and Unlock https://codeforces.com/contest/2278/problem/D
// Time    : 2026-10-31 22:41:32
#include <iostream>
#include <vector>
#include <algorithm>
#define cautor const auto &
#define autor auto &
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

vector<ll> Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;
    Sort(a);
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += (a[i] - a[i - 1]) * min(i, n - i);
    }
    return {ans, a.back() - a[0]};
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
