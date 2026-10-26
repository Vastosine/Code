// Problem : D. Connecting the Conflicts https://codeforces.com/contest/2272/problem/D
// Time    : 2026-10-26 22:36:09
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

struct Tree {
    vector<vi> e, f;
    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    Tree(int n) : e(n + 1), f(n + 1, vi(2)) {}

    void dfs(int u = 1) {
        f[u][1] = 1;
        for (int v : e[u]) {
            if (f[v][1]) continue;
            dfs(v);
            f[u][1] += f[v][0];
            f[u][0] += max(f[v][0], f[v][1]);
        }
    }
};
vector<Tree> a;

auto solve() {
    int n, p = -1;
    cin >> n;
    a.clear();
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m > 1) p = i;
        a.push_back(Tree(m));
        for (int j = 1; j < m; j++) {
            int u, v;
            cin >> u >> v;
            a[i].addEdge(u, v);
        }
        a[i].dfs();
        // cout << max(a[i].f[0], a[i].f[1]) << " ";
    }
    if (p < 0) {
        for (int i = 2; i <= n; i++) {
            cout << "1 1 " << i << " 1\n";
        }
    } else {
        int u = 1;
        if (a[p].f[1][0] < a[p].f[1][1]) u = a[p].e[1][0];
        for (int i = 0; i < n; i++) {
            if (i != p) {
                cout << p + 1 << " " << u << " " << i + 1 << " " << 1 << "\n";
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}