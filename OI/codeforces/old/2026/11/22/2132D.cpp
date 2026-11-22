// Problem : D. From 1 to Infinity https://codeforces.com/problemset/problem/2132/D
// Time    : 2026-11-22 08:51:45
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

vll s, D, F;

void init() {
    s.assign(10, 0);
    for (int i = 1; i < 10; i++) s[i] = s[i - 1] + i;
    D.assign(16, 1);
    for (int i = 1; i < 16; i++) D[i] = D[i - 1] * 10;
    F.assign(16, 0);
    for (int i = 1; i < 16; i++) F[i] = F[i - 1] + 9 * D[i - 1] * i;
    // cout << s << "\n" << D << "\n" << F << "\n";
}

auto Main([[maybe_unused]] int C = 0) {
    ll n;
    cin >> n;
    int k = upper_bound(F.begin(), F.end(), n) - 1 - F.begin();
    ll x = (n - F[k]) / (k + 1) - 1 + D[k], ans = 0, q = (n - F[k]) % (k + 1);
    for (int i = 0; i < 15; i++) {
        ll y = x / D[i], d = y % 10;
        if (!y) break;
        ans += (y / 10 * s[9] + (d ? s[d - 1] : 0)) * D[i] + d * (x % D[i] + 1);
    }
    if (q) {
        string t = to_string(x + 1);
        for (int i = 0; i < q; i++) ans += t[i] - '0';
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
