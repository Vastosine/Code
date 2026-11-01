// Problem : C. Classy Numbers https://codeforces.com/problemset/problem/1036/C
// Time    : 2026-11-02 06:35:02
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


ll CC(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    ll ans = 1;
    for (ll i = 0; i < m; i++) {
        ans = ans * (n - i) / (i + 1);
    }
    return ans;
}

ll pow(ll x, ll n) {
    ll ans = 1;
    while (n--) ans *= x;
    return ans;
}

vector<vector<ll>> F;
ll f(int k, int x, int d = 1) {
    if (d > 1) return (d - 1) * f(k, x - 1) + f(k, x);
    if (F[k][x]) return F[k][x];
    return F[k][x] = x ? CC(k, x) * pow(9, x) + f(k, x - 1) : 1; 
}

ll g(ll x) {
    ll st = 0, y = 1;
    while (y <= x / 10) y *= 10, st++;
    ll ans = 0, t = 3;
    while (~st) {
        bool k = 0;
        if ((k = y <= x) && t > 0) {
            ans += f(st, t, x / y);
            x -= y * (x / y);
        }
        t -= k;
        st--;
        y /= 10;
    }
    return ans + 1;
}

void init() {
    F.assign(19, vector<ll>(4));
}

auto Main([[maybe_unused]] int C = 0) {
    ll l, r;
    cin >> l >> r;
    return g(r) - g(l - 1);
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

// CHECK 上限       -> OK