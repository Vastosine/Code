// Problem : 幻想乡树状结界 https://ac.nowcoder.com/acm/contest/142131/L
// Time    : 2026-10-18 17:13:32
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
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
template<typename T, typename... Args> void asv(int n, T &&v, vector<Args>&... args) { (..., args.assign(n, v)); }
template<typename F, typename T, typename... Args> T &update(F &&f, T &x, Args &&...args) { return ((x = f(x, args)), ...), x; }
template<typename F, typename T, typename... Args> T func(F &&f, const T &x, Args &&...args) { T tmp(x); return ((tmp = f(tmp, args)), ...), tmp; }

vector<vi> e;
vector<vector<vi>> ava;
vi a, sp, vis, c;
int n, k;

bool search(int u, int i = 2, int s = 0) {
    if (i > n) {
        if (s) return false;
        ava[u].push_back({});
        for (int j = 1; j <= n; j++) if (vis[j]) ava[u].back().push_back(j);
        return true;
    }
    if (i == u) return search(u, i + 1, s ^ a[i]);
    bool ans = search(u, i + 1, s);
    vis[i] = 1;
    ans |= search(u, i + 1, s ^ a[i]);
    vis[i] = 0;
    return ans;
}

vi V;

bool check(int u) {
    
}

bool dfs(int i) {
    if (i == k) {
        assign(n + 1, V);
    }
}

auto solve() {
    cin >> n >> k;
    assign(n + 1, e, a, ava, vis, c);
    sp.assign(k, 0);
    int s = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], s ^= a[i];
    cin >> sp;
    for (int i : sp) if (i == 1 && s) return -1ll;
    for (int u : sp) {
        if (u > 1 && !search(u)) return -1ll;
        sort(ava[u], [] (const vi &p, const vi &q) { return p.size() < q.size(); });
        // cout << ava[u] << "\n";
    }
    return 0ll;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    while (c--) cout << solve() << "\n";
    // while (c--) {
    //     vi ans = solve();
    //     if (ans.empty()) cout << "NO";
    //     else cout << "YES\n" << ans << "\n";
    // }
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}