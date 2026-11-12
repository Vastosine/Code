// Problem : G2. Lakeside Trail (Hard Version) https://codeforces.com/contest/2290/problem/G2
// Time    : 2026-11-12 22:35:23
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

ll need(vi a, int n, ll lim) {
    ll ans = 0;
    for (int i = 0, c = 0, di = 1; c <= n; c++, i = (i + di + n) % n) {
        di = 1;
        if (ll dx = -lim - a[i]; dx > 0) {
            a[i] += dx, a[(i + 1) % n] -= dx;
            c = 0;
            ans += dx;
        }
        if (ll dx = a[i] - lim; dx > 0) {
            a[i] -= dx, a[(i - 1 + n) % n] += dx;
            c = 0;
            ans += dx;
            di = -1;
        }
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    // need({100, 0, -100, 0}, 4, 2);
    ll n, k;
    cin >> n >> k;
    vi a(n), b(n);
    cin >> a;
    for (int i = 1; i <= n; i++) {
        b[i % n] = a[i % n] - a[i - 1];
    }
    ll l = -1, r = 1 << 30;
    while (l < r - 1) {
        ll x = (l + r) >> 1;
        ll nd = need(b, n, x);
        if (nd <= k) r = x;
        else l = x;
    }
    return r;
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
