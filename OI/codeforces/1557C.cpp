// Problem : C. Moamen and XOR https://codeforces.com/problemset/problem/1557/C
// Time    : 2026-10-28 19:28:37
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

const ll M = 1e9 + 7;

ll pow(ll x, ll n) {
    return n ? pow(x * x % M, n / 2) % M * (n & 1 ? x : 1ll) % M : 1ll;
}

auto solve() {
    ll n, k;
    cin >> n >> k;
    ll a, b, c;
    c = (pow(2, n - 1) - (n & 1) + M) % M;
    a = !(n & 1);
    b = (pow(2, n) - a - c + M * 2) % M;
    vector<ll> f(k + 1);
    f[0] = 1;
    for (int i = 1; i <= k; i++) {
        f[i] = (f[i - 1] * b + a * pow(2, n * (i - 1))) % M;
    }
    return f[k];
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