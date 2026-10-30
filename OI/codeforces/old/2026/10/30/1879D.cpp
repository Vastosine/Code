// Problem : D. Sum of XOR Functions https://codeforces.com/problemset/problem/1879/D
// Time    : 2026-10-30 13:07:17
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

const int M = 998244353;

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<vector<ll>> f(n, vector<ll>(31)), g = f, a(n, vector<ll> (31));
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int k = 0; x; k++) {
            a[i][k] = x % 2;
            x /= 2;
        }
        // cout << a[i] << "\n";
    }
    ll ans = 0;
    for (ll k = 0; k < 31; k++) {
        ll res = f[0][k] = g[0][k] = a[0][k];
        for (ll i = 1; i < n; i++) {
            if (a[i][k]) {
                g[i][k] = i - g[i - 1][k] + 1;
                f[i][k] = (i * (i + 1)) / 2 - f[i - 1][k] + g[i][k];
            } else {
                g[i][k] = g[i - 1][k];
                f[i][k] = f[i - 1][k] + g[i][k];
            }
            res += f[i][k];
        }
        ans = (ans + res % M * ((1 << k) % M)) % M;
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
