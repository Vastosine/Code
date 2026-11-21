// Problem : C. Chipmunk Theo and Equality https://codeforces.com/contest/2231/problem/C
// Time    : 2026-11-21 15:20:06
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
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    Sort(a);
    if (a[0] == a.back()) return 0;
    auto f = [&] (int &x, int &res) {
        x = x & 1 ? x + 1 : x / 2;
        res++;
    };
    auto check = [&] (int target) {
        int res = 0;
        for (int i : a) {
            while (i > target || (i == target - 1 && (i & 1))) f(i, res);
            if (i != target) return inf;
        }
        return res;
    };
    int ans = inf, c = 0;
    int vis[3]{};
    while (true) {
        ans = min(ans, check(a[0]) + c);
        if (a[0] < 3) vis[a[0]] = 1;
        f(a[0], c);
        if (a[0] < 3 && vis[a[0]]) break;
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
