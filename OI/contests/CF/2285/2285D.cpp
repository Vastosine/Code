// Problem : D. Reverse Partition https://codeforces.com/contest/2285/problem/D
// Time    : 2026-11-15 22:35:12
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
const int M = 1e9 + 7;

ll qpow(ll x, ll n) {
    x = (x % M + M) % M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

vll F;
void init() {
    int n = 1e6;
    F.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % M;
}

ll Cnk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return F[n] * inv(F[k] * F[n - k] % M) % M;
}

using mii = map<int, int>;

mii operator+=(mii &p, const mii &q) {
    for (auto &[u, v] : q) {
        p[u] += v;
    }
    return p;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, k;
    cin >> n >> m >> k;
    vll a(n);
    cin >> a;
    vll p(n), q(n);
    vll data(n - 1);
    map<ll, vll> mp;
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] + a[i - 1];
        q[i] = q[i - 1] + a[n - i];
        data[i - 1] = q[i] - p[i];
        mp[data[i - 1]].push_back(i);
    }
    for (auto &[u, v] : mp) Sort(v);
    auto query = [&] (ll l, ll r, ll x) -> int {
        if (mp.find(x) == mp.end()) return 0;
        const vll &t = mp[x];
        return lower_bound(t.begin(), t.end(), r) - lower_bound(t.begin(), t.end(), l);
    };
    int cnt = query(1, n, 0);
    while (k--) {
        ll i, v;
        cin >> i >> v;
        ll l = i, r = n - i + 1;
        if (l > r) swap(l, r), v = -v;
        ll x = cnt + query(l, r, v);
        x += - query(l, r, 0);
        cout << Cnk(x, m - 1) << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cout << Cnk(100, 6) << "\n";
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
