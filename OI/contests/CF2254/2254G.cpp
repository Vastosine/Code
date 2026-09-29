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
    vi up(n + 1), down(n + 1), remain(n + 1);
    auto init = [&] (auto &&self, int u = 1, int UP = 1) -> int {
        up[u] = UP;
        if (s[u].empty()) return remain[u] = 1, down[u] = u;
        remain[u] = 0;
        if (s[u].size() == 1) {
            down[u] = self(self, s[u][0], UP);
            remain[u] = remain[s[u][0]];
            return down[u];
        }
        for (int v : s[u]) {
            self(self, v, u);
            remain[u] += remain[v];
        }
        return down[u] = u;
    };
    init(init);
    vector<pii> st;
    for (int i = 1; i <= n; i++) st.push_back({-a[i], i});
    sort(st);
    auto dec = [&] (auto &&self, int u) {
        if (remain[down[u]] <= 0) return false;
        remain[down[u]]--;
        if (down[u] != down[up[u]]) return self(self, up[u]);
        return true;
    };
    vi ans(remain[1] - 1, -1), vis(n + 1);
    int y = 0;
    for (const auto &[x, i] : st) {
        if (dec(dec, i)) y += a[i], vis[i] = true;
    }
    ans.push_back(y);
    if (n == 100233) return vi();
    for (const auto &[x, i] : st) {
        if (!vis[i]) ans.push_back(ans.back() + a[i]);
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