// Problem : C. Minimizing the Sum https://codeforces.com/problemset/problem/1969/C
// Time    : 2026-11-21 11:45:59
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

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    vll a(n + 1);
    vector<vll> f(n + 1, vll(k + 1, INF));
    f[0].assign(k + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 0; j <= k; j++) {
            f[i][j] = f[i - 1][j] + a[i];
            for (int t = 0; t <= min(i - 1, j); t++) {
                f[i][j] = min(f[i][j], f[i - t - 1][j - t] + (t + 1) * *min_element(a.begin() + i - t, a.begin() + i + 1));
            }
            if (j) f[i][j] = min(f[i][j], f[i][j - 1]);
        }
        // cout << f[i] << "\n";
    }
    return f.back()[k];
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
