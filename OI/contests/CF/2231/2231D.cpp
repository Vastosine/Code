// Problem : D. Maximum Prefix Sums https://codeforces.com/contest/2231/problem/D
// Time    : 2026-11-21 15:20:06
#include <algorithm>
#include <cassert>
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

const ll extra = 1e12;

vll Main([[maybe_unused]] int C = 0) {
    int n;
    string s;
    cin >> n >> s;
    vll a(n), c(n), b(n, INF);
    cin >> a >> c;
    b[0] = c[0];
    vi o(1, 0);
    for (int i = 1; i < n; i++) {
        if (c[i] != c[i - 1]) b[i] = c[i], o.push_back(i);
        if (c[i] < c[i - 1]) return {};
    }
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        if (u && s[u] == '1') {
            if (b[u - 1] == INF) b[u - 1] = b[u] - a[u], o.push_back(u - 1);
        }
        if (u < n - 1 && s[u + 1] == '1') {
            if (b[u + 1] == INF) b[u + 1] = b[u] + a[u + 1], o.push_back(u + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (b[i] == INF) {
            if (s[i] == '1') b[i] = b[i - 1] + a[i];
            else b[i] = c[i] - extra;
        }
    }
    auto check = [&] () {
        if (s[0] == '1' && a[0] != b[0]) return false;
        for (int i = 1; i < n; i++) {
            if ((s[i] == '1' && a[i] != b[i] - b[i - 1]) || b[i] > c[i]) return false;
        }
        return true;
    };
    if (!check()) return {};
    for (int i = n - 1; i; i--) b[i] -= b[i - 1];
    return b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
