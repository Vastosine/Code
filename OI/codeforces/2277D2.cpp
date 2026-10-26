// Problem : D2. Number Operating (Hard Version) https://codeforces.com/contest/2277/problem/D2
// Time    : T26-10-25 12:14:58
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

#define gap(k) ((1ll << (k)) - 1)

const int M = 998244353, T = 10;

vector<ll> F(1 << T), s = F, s2(61), p(61);

ll A(ll x, int k) {
    return gap(k) - x + k;
}

ll f(ll);

ll B(ll x, int k) {
    return f(x - gap(k - 1) + 1) + k;
}

ll level(ll x) {
    ll k = 1;
    while (gap(k) < x) k++;
    return k;
}

ll f(ll x) {
    if (!x) return 0;
    if (x < (ll) F.size() && F[x]) return F[x];
    ll k = level(x);
    if (gap(k) == x) return k;
    ll ans = min(A(x, k), B(x, k));
    return ans;
}

ll g(ll st, ll len) {
    return (st * 2 + len - 1) * len / 2 % M;
}

ll S(ll n) {
    if (n <= 0) return 0;
    if (n < (ll) s.size()) return s[n];
    ll k = level(n);
    if (n == gap(k) && s2[k]) return s2[k];
    ll t = gap(k) - p[k];
    if (n > t) {
        ll d = n - t;
        ll ans = (S(t) + g(k + gap(k) - n, d)) % M;
        if (n == gap(k)) s2[k] = ans;
        return ans;
    } 
    ll m = n - gap(k - 1);
    return (S(gap(k - 1)) + S(m + 1) - 1 + m % M * k) % M;
}

auto solve() {
    ll l, r;
    cin >> l >> r;
    // for (ll i = l; i <= r; i++) (ans += f(i)) %= M;
    return (S(r) + M - S(l - 1)) % M;
}

void init() {
    F[1] = 1, F[2] = 3, F[3] = 2;
    for (int i = 1; i < (1 << T); i++) s[i] = s[i - 1] + (F[i] = f(i));
    for (int k = 0; k <= T; k++) s2[k] = s[gap(k)];
    for (ll k = 1; k < 61; k++) {
        ll cnt;
        for (cnt = 1; cnt <= (1ll << (k - 1)) && A((1ll << k) - cnt, k) <= B((1ll << k) - cnt, k); cnt++);
        p[k] = cnt - 1;
        // cout << p[k] << "\n";
    }
    // for (int k = T + 1; k < 60; k++) {
    //     s2[k] = (2 * s2[k - 1] + k * ((gap(k - 1) - 1) % M) - 1) % M;
    //     s2[k] -= (s.back() - s[(1ll << T) - p[k] + 1] + (p[k] - 2) * (k)) % M;
    //     (s2[k] += g(k, p[k]) + M) %= M;
    //     // s2[k + 1] = 2 * s2[k] + (k + 1) * ((1ll << k)) - 1 + f(gap(k) + 1) + f(gap(k) + 2);
    //     // int l = (1ll << (T)) - p[k + 1];
    //     // s2[k + 1] -= (k + 1 - F.back()) * p[k + 1] + s.back() - s[l - 1];
    //     // s2[k + 1] += g(k + 1, p[k + 1]);
    //     // cout << s2[k + 1] << "\n";
    // }
    // for (ll i : s2) cout << i << "\n";
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    init();
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}