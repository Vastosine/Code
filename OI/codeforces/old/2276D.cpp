// Problem : D. Caveman https://codeforces.com/contest/2276/problem/D
// Time    : 2026-10-15 18:39:37
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
int n, m;
vector<vi> e;
vi dfn, vis;

void addEdge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}

bool dfs(int u, int d = 1) {
    dfn[u] = d;
    for (int v : e[u]) {
        if ((dfn[v] && dfn[u] - dfn[v] > 1) || (!dfn[v] && dfs(v, d + 1))) return true;
    }
    return false;
}

// void check(int u) {
//     if (vis[u]) return;
//     vis[u] = true;
//     for (int v : e[u]) {
//         check(v);
//     }
// }

vi V;

using std::max;

int Dfs(int u, int &ans) {
    if (V[u]) return 0;
    V[u] = 1;
    vi p;
    for (int v : e[u]) {
        p.push_back(Dfs(v, ans));
    }
    sort(p);
    if (p.empty()) return 1;
    if (p.size() == 1) return ans = max(ans, 1 + p[0]), 1 + p[0];
    ans = max(ans, 1 + p.back() + p[p.size() - 2]);
    return 1 + p.back();
}

vi VIS;

bool DFS(int u) {
    if (VIS[u]) return 0;
    VIS[u] = 1;
    for (int v : e[u]) if (VIS[v]) DFS(v);
    return 1;
}

auto solve() {
    cin >> n >> m;
    assign(n + 1, e, dfn, vis, V, VIS);
    while (m--) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }
    bool ans = false;
    int t = 0;
    for (int i = 1; i <= n; i++) {
        t += !dfn[i];
        if (e[i].empty()) return "Brain Melt";
        ans |= dfs(i);
    }
    if (ans) return "Many";
    int x = 0;
    Dfs(1, x);
    for (int i = 1; i <= n; i++) {
        t += !DFS(i);
    }
    if (t > 1) return "Many";
    return x > 3 ? "Many" : "2";
    // int x = 0;
    // return Dfs(1, x), x;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
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