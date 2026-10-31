// Problem : C. Primes and Multiplication https://codeforces.com/problemset/problem/1228/C
// Time    : 2026-10-31 07:53:00
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

const int M = 1e9 + 7;

ll qpow(ll x, ll n) {
    return n ? qpow(x * x % M, n / 2) % M * ((n & 1) ? x : 1) % M : 1;
}

auto Main([[maybe_unused]] int C = 0) {
    ll x, n, ans = 1;
    vi lst;
    cin >> x >> n;
    for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) lst.push_back(p);
        while (x % p == 0) x /= p;
    }
    if (x > 1) lst.push_back(x);
    for (ll p : lst) {
        ll t = 0, y = n;
        while (y /= p) t += y;
        ans = ans * qpow(p, t) % M;
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
