// Problem : C. Reverse and Double https://codeforces.com/contest/2280/problem/C
// Time    : 2026-11-15 10:10:36
#include <iostream>
#include <vector>
#include <algorithm>
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

int f(const vi &a, int l = -1, int r = -1) {
    int ans = 0, n = (int) a.size();
    for (int i = 1; i < n; i++) {
        if (i == l || i == r + 1) continue;
        ans = max(ans, abs(a[i] - a[i - 1]) * (i > l && i <= r ? 2 : 1));
    }
    if (l >= 0 && r >= 0) ans = max({ans, abs(2 * a[l] - (r < n - 1 ? a[r + 1] : a[l] * 2)), abs(a[r] * 2 - (l ? a[l - 1] : a[r] * 2))});
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int ans = f(a);
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            ans = min(ans, f(a, l, r));
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
