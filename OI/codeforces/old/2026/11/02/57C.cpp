// Problem : C. Array https://codeforces.com/problemset/problem/57/C
// Time    : 2026-11-02 07:13:25
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

const int M = 1e9 + 7;
vector<ll> F;
void init() {
    int n = 2e5 + 1;
    F.assign(n, 1);
    for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % M;
}

ll qpow(ll x, ll n) {
    x %= M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

ll CC(ll n, ll k) {
    return F[n] * inv(F[n - k] * F[k] % M) % M;
}

auto Main([[maybe_unused]] int C = 0) {
    ll n;
    cin >> n;
    return ((2 * CC(2 * n - 1, n) - n) % M + M) % M;
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

// CHECK n=1        -> 1
// CHECK 减法负值    ->      // 2*C - n 可能是负数
// CHECK 阶乘上界    ->      // 需要到 2n-1 = 199999