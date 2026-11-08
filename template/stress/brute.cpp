// Problem : C. Classy Numbers https://codeforces.com/problemset/problem/1036/C
// Time    : 2026-11-03 07:41:29
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
// [[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
// template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
// template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
// template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
// template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
// template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

ll CC(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    ll ans = 1;
    for (int i = 0; i < m; i++) {
        ans = ans * (n - i) / (i + 1);
    }
    return ans;
}

ll qpow(ll x, ll n) {
    return n ? qpow(x * x, n / 2) * (n & 1 ? x : 1) : 1;
}

vector<vector<ll>> F;
void INIT() {
    F.assign(19, vector<ll>(4));
    vector<ll> x(4);
    for (int i = 0; i <= 18; i++) {
        F[i][0] = CC(i, 0);
        for (int j = 1; j <= 3; j++) {
            F[i][j] = F[i][j - 1] + CC(i, j) * qpow(9, j);
        }
    }
}

ll f(ll x) {
    ll k = 0, y = 1, ans = 0, t = 3;
    while (y <= x / 10) y *= 10, k++;
    while (~k) {
        if (t && y <= x) {
            ans += F[k][t] + (x / y - 1) * (k ? F[k][t - 1] : 1);
            t--;
            x -= x / y * y;
        }
        k--;
        y /= 10;
    }
    return ans + 1;
}

auto bruteSolve(const string &s) {
    ll l, r;
    sscanf(s.c_str(), "%lld%lld", &l, &r);
    return f(r) - f(l - 1);
}

// int main() {
//     ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//     const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
//     cin >> C;
//     for (int c = 0; c < C; c++) {
//         auto ans = Main(c);
//         cout << ans << "\n";
//         // cout << OUT[ans] << "\n";
//         // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
//     }
//     return 0;
// }
