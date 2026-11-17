// Problem : P1605 迷宫 https://www.luogu.com.cn/problem/P1605
// Time    : 2026-08-05 09:23:51

#include <iostream>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
#define F(f, x) (f)[(x).first][(x).second]
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename A, typename B> std::istream &operator>>(std::istream &in, std::pair<A, B> &x) { return in >> x.first >> x.second; }
bool available(const pii &x, int n, int m) { return x.first > 0 && x.second > 0 && x.first <= n && x.second <= m; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

int n, m, k;
vector<vi> a, vis, f;
pii st, ed;
const pii NEXT[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int dfs(const pii &u = st) {
    if (u == ed) return 1;
    // if (~F(f, u)) return F(f, u);
    F(vis, u) = true;
    int ans = 0;
    for (const pii &i : NEXT) {
        pii v = u + i;
        if (!available(v, n, m) || F(vis, v) || F(a, v)) continue;
        ans += dfs(v);
    }
    F(vis, u) = false;
    return F(f, u) = ans;
}

void solve() {
    cin >> n >> m >> k >> st >> ed;
    a.assign(n + 1, vi(m + 1, 0));
    f.assign(n + 1, vi(m + 1, -1));
    vis.assign(n + 1, vi(m + 1, 0));
    while (k--) {
        pii x;
        cin >> x;
        F(a, x) = 1;
    }
    cout << dfs();
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}