// Problem : C. Travelling Salesman and Special Numbers https://codeforces.com/problemset/problem/914/C
// Time    : 2026-11-01 14:06:46
#include <bitset>
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
vector<ll> J;
void init() {
    int n = 1001;
    J.assign(n, 1);
    for (int i = 1; i < n; i++) J[i] = J[i - 1] * i % M;
}


ll qpow(ll x, ll n) {
    x %= M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

ll CC(int n, int m) {
    if (m > n || m < 0) return 0;
    return J[n] * inv(J[m] * J[n - m] % M) % M;
}

auto Main([[maybe_unused]] int C = 0) {
    bitset<1001> a;
    int k;
    cin >> a >> k;
    if (!k) return 1ll;  // 1st RE
    vector<vector<ll>> f(k + 1, vector<ll> (1001));
    for (int i = 1; i < 1001; i++) { // int i = 0 -> 2nd WA
        ll ans = 0, st, t = i;
        for (st = 1000; ~st; st--) {
            if (a[st]) break;
        }
        while (~st) {
            if (a[st]) (ans += CC(st, t)) %= M;
            t -= a[st];
            st--;
        }
        ans += !t;
        f[1][i] = ans % M;
    }
    f[1][1]--; // 3rd WA
    for (int i = 1; i < k; i++) {
        for (int j = 0; j <= 1000; j++) f[(i + 1) % 2][j] = 0;
        for (int j = 2; j <= 1000; j++) {
            (f[(i + 1) % 2][__builtin_popcount(j)] += f[i % 2][j]) %= M;
        }
    }
    return f[k % 2][1];
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
