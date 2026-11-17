// Problem : P4913 【深基16.例3】二叉树深度 https://www.luogu.com.cn/problem/P4913
// Time    : 2026-08-05 20:14:23

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename A, typename B> std::istream &operator>>(std::istream &in, std::pair<A, B> &x) { return in >> x.first >> x.second; }

vector<pii> c;
vector<int> h;

int dfs(int u) {
    if (~h[u]) return h[u];
    if (!u) return 0;
    return h[u] = std::max(dfs(c[u].first), dfs(c[u].second)) + 1;
}

void solve() {
    int n;
    cin >> n;
    c.assign(n + 1, {});
    h.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, dfs(i));
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}