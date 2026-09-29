// Problem : G. Nightcrawler https://codeforces.com/contest/2254/problem/G
// Time    : 2026-09-28 16:22:05
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

auto solve() {
    int n;
    cin >> n;
    vi a(n + 1), f(n + 1);
    vector<vi> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) cin >> f[i], s[f[i]].push_back(i);
    vi vis(n + 1);
    auto dfs = [&] (auto &&self, int u) -> int {
        if (s[u].empty()) return u;
        if (s[u].size() == 1) {
            int v = s[u][0];
            int x = self(self, v);
            return a[u] > a[x] ? u : x;
        } 
        int min = -1;
        for (int v : s[u]) {
            int x = self(self, v);
            vis[x] = true;
            if (!~min || a[min] > a[x]) min = x;
        }
        vis[min] = false;
        int ret = a[u] > a[min] ? u : min;
        return ret;
    };
    vis[dfs(dfs, 1)] = true;
    vi list;
    int st = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) list.push_back(a[i]);
        else st += a[i];
    }
    vi ans(n - list.size() - 1, -1);
    sort(list, [] (int x, int y) { return x > y; });
    ans.push_back(st);
    for (int x : list) {
        ans.push_back(ans.back() + x);
    }
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}