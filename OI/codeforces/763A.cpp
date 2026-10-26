// Problem : A. Timofey and a tree https://codeforces.com/problemset/problem/763/A
// Time    : 2026-10-26 14:14:53
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

int n;
vector<vi> e;
vi c, vis;

bool check(int u, int r) {
    vis[u] = 1;
    for (int v : e[u]) {
        if (vis[v]) continue;
        if (u != r && c[v] != c[u]) return false;
        if (!check(v, r)) return false;
    }
    return true;
}

auto solve() {
    cin >> n;
    assign(n + 1, e, c, vis);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> c[i];
    set<int> p;
    for (int u = 1; u <= n; u++) {
        for (int v : e[u]) {
            if (c[v] != c[u]) {
                p.insert(u);
                break;
            }
        }
    }
    vi may;
    for (int u : p) {
        int cnt = 0;
        for (int v : e[u]) {
            cnt += p.find(v) != p.end();
        }
        if (cnt > 1) may.push_back(u);
    }
    if (p.empty()) return 1;
    if (may.empty()) {
        for (int u : p) {
            if (check(u, u)) return u;
            vis.assign(n + 1, 0);
        }
        return -1;
    }
    if (may.size() > 1) return -1;
    if (check(may[0], may[0])) return may[0];
    else return -1;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int C = 1;
    // cin >> c;
    while (C--) {
        int x = solve();
        if (x < 0) cout << "NO\n";
        else cout << "YES\n" << x << "\n";
    }
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}