// Problem : T812406 [ICPC 2026 Nanchang I] Little Z's Function https://www.luogu.com.cn/problem/T812406?contestId=372198
// Time    : 2026-11-19 13:00:05
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
vi primes, phi;
int maxn = 5e5;
void init() {
    vector<bool> is(maxn, 1);
    phi.assign(maxn, 0);
    for (ll i = 2; i < maxn; i++) {
        if (is[i]) primes.push_back(i), phi[i] = i - 1;
        for (int p : primes) {
            if (i * p >= maxn) break;
            is[i * p] = 0;
            phi[i * p] = phi[i] * (i % p ? p - 1 : p);
            if (i % p == 0) break;
        }
        cout << phi[i] << "\n";
    }
}

auto Main([[maybe_unused]] int C = 0) {
    return 0;
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
