// Problem : D. Sanae, Cross and Color https://codeforces.com/problemset/problem/2228/D
// Time    : 2026-11-22 13:55:17
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
void init() {}

template<typename T>
void er(vector<T> & a) {
    Sort(a);
    a.erase(unique(a.begin(), a.end()), a.end());
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<pii> a(n);
    cin >> a;
    er(a);
    n = (int) a.size();
    vi x, y;
    for (auto &[u, v] : a) x.push_back(u), y.push_back(v);
    er(x);
    er(y);
    for (auto &[u, v] : a) {
        u = lower_bound(x.begin(), x.end(), u) - x.begin();
        v = lower_bound(y.begin(), y.end(), v) - y.begin();
    }
    int xl = (int) x.size();
    vi premax(xl, -1), premin(xl, inf), sufmax(xl, -1), sufmin(xl, inf);
    for (auto &[u, v] : a) {
        premax[u] = max(premax[u], v);
        premin[u] = min(premin[u], v);
        sufmax[u] = max(sufmax[u], v);
        sufmin[u] = min(sufmin[u], v);
    }
    for (int i = 1; i < xl; i++) {
        premax[i] = max(premax[i], premax[i - 1]);
        premin[i] = min(premin[i], premin[i - 1]);
    }
    for (int i = xl - 2; ~i; i--) {
        sufmax[i] = max(sufmax[i], sufmax[i + 1]);
        sufmin[i] = min(sufmin[i], sufmin[i + 1]);
    }
    ll ans = 0;
    vi l(xl), r(xl);
    for (int i = 1; i < xl; i++) {
        r[i] = min(premax[i - 1], sufmax[i]);
        l[i] = max(premin[i - 1], sufmin[i]);
        ans += max(0, r[i] - l[i]);
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
