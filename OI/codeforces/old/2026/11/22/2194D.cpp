// Problem : D. Table Cut https://codeforces.com/problemset/problem/2194/D
// Time    : 2026-11-22 09:39:07
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
    int n, m;
    cin >> n >> m;
    vector<vi> a(n, vi(m));
    cin >> a;
    auto s = a;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j; j--) s[i][j - 1] += s[i][j];
        sum += s[i][0];
    }
    string ans;
    ll t = sum / 2;
    cout << t * (sum - t) << "\n";
    for (int i = 0; i < n; i++) {
        if (t >= s[i][0]) {
            t -= s[i][0];
            ans.push_back('D');
        } else {
            int j;
            for (j = 0; j < m && s[i][j] != t; j++) {
                ans.push_back('R');
            }
            ans.push_back('D');
            for (; j < m; j++) {
                ans.push_back('R');
            }
            while ((int) ans.size() < n + m) ans.push_back('D');
            break;
        }
    }
    while ((int) ans.size() < n + m) ans.push_back('R');
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
