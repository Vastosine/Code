#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

szt n, M;
ll qpow(ll x, ll n, ll m = M) {
    x = (x % m + m) % m;
    ll res = 1;
    while (n) {
        if (n & 1) (res *= x) %= m;
        x = x * x % m;
        n >>= 1;
    }
    return res % m;
}

// m need to be prime
ll inv(ll x, ll m = M) {
    return qpow(x, m - 2, m);
}

auto Main(int = 0) {
    cin >> n >> M;
    vst f(n + 1);
    f[1] = 0;
    szt ans = 0;
    for (szt i = 2; i <= n; i++) {
        szt res = n, t = 0;
        for (szt j = 1; j <= n; j++) {
            szt g = gcd(i, j);
            (res += f[g]) %= M;
            if (g == i) t++;
        }
        // cout << res << "\n";
        f[i] = ((res *= inv(n - t))) %= M;
        ans += res;
    }
    // cout << f << "\n";
    return (ans * inv(n) + 1) % M;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
