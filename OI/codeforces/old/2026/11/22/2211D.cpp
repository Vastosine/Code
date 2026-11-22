// Problem : D. AND-array https://codeforces.com/problemset/problem/2211/D
// Time    : 2026-11-22 14:22:45
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
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
inline ll comb_pow(ll x, ll n, ll m) {
    x = (x % m + m) % m;
    ll r = 1;
    while (n) {
        if (n & 1) r = (ll)((__int128)r * x % m);
        x = (ll)((__int128)x * x % m);
        n >>= 1;
    }
    return r % m;
}

struct CnkPrime {
    static inline int p = 0;
    static inline std::vector<ll> fac, ifac;

    // 前提：mod 是质数、maxN < mod。两者都 assert。
    static void init(int maxN, int mod) {
        assert(maxN >= 0);
        assert(mod > 1);
        assert(maxN < mod && "CnkPrime 要求 maxN < p；n 会到 p 以上时用 CnkLucas");
        p = mod;
        fac.assign(maxN + 1, 1);
        ifac.assign(maxN + 1, 1);
        for (int i = 1; i <= maxN; i++) fac[i] = fac[i - 1] * i % p;
        ifac[maxN] = comb_pow(fac[maxN], p - 2, p);
        for (int i = maxN; i >= 1; i--) ifac[i - 1] = ifac[i] * i % p;
    }

    static ll get(int n, int k) {
        assert(p && "先 init");
        assert(n >= 0 && n < (int)fac.size() && "n 超出 init 的表");
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % p * ifac[n - k] % p;
    }

    static bool fits(int n) { return p && n >= 0 && n < (int)fac.size(); }
};
const int M = 1e9 + 7, N = 1e5 + 1;
CnkPrime cnk;
void init() {
    cnk.init(N, M);
}


auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    const int B = 29;
    vll b(n + 1), c(B);
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int k = n; k; k--) {
        ll s = 0;
        for (int i = 0; i < B; i++) {
            if (c[i]) (s += (cnk.get(c[i], k) << i) % M) %= M;
        }
        int add = (b[k] + M - s) % M;
        for (int i = 0; i < B; i++) {
            if ((1 << i) & add) c[i] = k;
        }
    }
    vi ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < B; j++) {
            if (c[j] > i) ans[i] |= (1 << j);
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
