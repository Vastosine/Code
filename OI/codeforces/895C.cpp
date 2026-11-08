// Problem : C. Square Subsets https://codeforces.com/problemset/problem/895/C
// Time    : 2026-11-08 10:00:24

// a[i] >= K 时计数错误
// a[i] >= K 时，记a[i] = x的数量为k，则 ans *= 1 + C(k, 2) + C(k, 4) + ... （取模省略）

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
vi primes;
void init() {
    int n = 70;
    vi is(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i);
        for (int p : primes) {
            if (i * p > n) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

int f(int x) {
    int y = 0;
    for (int i = (int) primes.size() - 1; ~i; i--) {
        y *= 2;
        int p = primes[i];
        while (x % p == 0) {
            x /= p;
            y ^= 1;
        }
    }
    return y;
}

const int M = 1e9 + 7, K = 1 << 11;

// x -> prime plite mask
// state: f[i][mask] (mask < (1 << 11))
// transfer: f[i + 1][mask ^ a[i + 1]] += f[i][mask]
//           f[i + 1][mask] += f[i][mask]
// to a[i] > (1 << 11) special 
// complexity: 1e5 * 2048
// border: no
auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    for (int &i : a) i = f(i);
    Sort(a);
    vector<vector<ll>> f(2, vector<ll>(K));
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
    for (int c = 0; i < n; i++) {
        if (!i || a[i] != a[i - 1]) c = 0;
        c++;
        if (c > 1) {
            c -= 2;
            ans = (ans * 2) % M;
        }
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