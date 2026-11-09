// Problem : C. Square Subsets https://codeforces.com/problemset/problem/895/C
// Time    : 2026-11-09 11:14:02
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }

const int M = 1e9 + 7, K = 1 << 11;
vi primes;
vll F;
void init() {
    int m = 70;
    vi is(m + 1, 1);
    for (int i = 2; i <= m; i++) {
        if (is[i]) primes.push_back(i);
        for (int p : primes) {
            if (i * p > m) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
    int n = 1e5;
    F.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % M;
}

ll qpow(ll x, ll n) {
    x %= M;
    return n ? qpow(x * x, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

ll C(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    return F[n] * inv(F[n - m] * F[m] % M) % M;
}

ll g(int n) {
    ll ans = 0;
    for (int i = 0; i <= n; i += 2) {
        (ans += C(n, i)) %= M;
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m = (int) primes.size();
    cin >> n;
    vi a(n);
    cin >> a;
    for (int &x : a) {
        int y = 0;
        for (int i = 0; i < m; i++) {
            int p = primes[i];
            while (x % p == 0) y ^= (1 << i), x /= p;
        }
        x = y;
    }
    Sort(a);
    // 2 3 5 7 11 13 17 19 23 29 31
    vector<vll> f(2, vll(K));
    f[0][0] = 1;
    int i;
    for (i = 0; i < n && a[i] < K; i++) {
        for (int j = 0; j < K; j++) f[(i + 1) % 2][j] = 0;
        for (int j = 0; j < K; j++) {
            (f[(i + 1) % 2][j ^ a[i]] += f[i % 2][j]) %= M;
            (f[(i + 1) % 2][j] += f[i % 2][j]) %= M;
        }
    }
    ll ans = f[i % 2][0];
    vi p;
    for (; i < n; i++) {
        if (!i || a[i] != a[i - 1]) p.push_back(0);
        p.back()++;
    }
    for (int x : p) {
        (ans *= g(x)) %= M;
    }
    return (ans - 1 + M) % M; 
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
