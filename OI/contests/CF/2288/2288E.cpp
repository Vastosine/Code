// Problem : E. Cirno and the Math Problem https://codeforces.com/contest/2288/problem/E
// Time    : 2026-11-21 22:35:26
#include <algorithm>
#include <iostream>
#include <numeric>
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

int f(int n, int m) {
    int ans = 0;
    auto dfs = [&] (auto &&f, int n, int m, int pre = -1) {
        if (!n) return ans ^= 1, void();
        for (int i = max(1, pre + 1); i <= m; i++) {
            if (gcd(pre, i) == 1) {
                f(f, n - 1, m, i);
            }
        }
    };
    dfs(dfs, n, m);
    return ans;
}


void init() {
    int n = 25;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << f(i, j);
        }
        cout << "\n";
    }
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    // m -= n;
    // int k = 0;
    // while ((1 << (k + 1)) <= n) k++;
    // while (true) {
    //     while ((1 << k) > n) k--;
    //     if (m % (1 << (k + 1)) >= ((1 << (k + 1)) - n)) return 0;
    //     n -= (1 << (k - 1));
    //     m %= (1 << (k - 1));
    // }
    return f(n, m);
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
