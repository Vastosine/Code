// Problem : F. Problem from Malinovka https://codeforces.com/contest/2289/problem/F
// Time    : 2026-11-22 17:05:17
#include <algorithm>
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
vi f;
vi primes;
vector<bool> is;
void sieve(int n) {
    is.assign(n + 1, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i);
        for (int p : primes) {
            if (1ll * i * p > n) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}
void init() {
    sieve(1e6);
    int n = 1e6;
    f.assign(n + 1, 0);
    for (int i = 1; i * i <= n; i++) {
        f[i * i] = i;
    }
    for (int i = 1; i <= n; i++) if (!f[i]) f[i] = f[i - 1];
}

vi use;

ll Dfs(ll n, ll s, int i = 0, ll t = 1) {
    if (i == (int) use.size()) return (t <= s / t) * f[n / t] * f[n / (s / t)];
    return Dfs(n, s, i + 1, t) + Dfs(n, s, i + 1, t * use[i]);
}

ll dfs(ll n, int i = 0, ll s = 1) {
    if (i >= (int) primes.size() || s * primes[i] > n) {
        if (s == 1) return 0;
        return f[n / s] * Dfs(n, s);
    }
    ll p = primes[i];
    // if (p * p > n && s == 1) return 0;
    ll ans = 0;
    ans += dfs(n, i + 1, s);
    use.push_back(p);
    ans += dfs(n, i + 1, s * p);
    use.pop_back();
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    ll ans = f[n] * f[n] * f[n];
    return ans + dfs(n) * 3;
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
