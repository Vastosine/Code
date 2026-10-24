// Problem : D2. Tree Coloring (Hard Version) https://codeforces.com/problemset/problem/2183/D2
// Time    : 2026-10-17 22:23:46
#include <iostream>
#include <set>
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

vector<std::set<int>> a, e;
vi dep, cnt, ss, er;

void dfs(int u = 1, int d = 1) {
    if (dep[u]) return;
    dep[u] = d;
    cnt[d]++;
    a[d].insert(u);
    for (int v : e[u]) {
        dfs(v, d + 1);
    }
}

using std::max;

auto solve() {
    int n;
    cin >> n;
    assign(n + 1, e, dep, cnt, ss, er, a);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].insert(v);
        e[v].insert(u);
        ss[u]++;
        ss[v]++;
    }
    dfs();
    ss[1]++;
    vector<vi> ans;
    for (int d = n; d; d--) {
        for (int u : a[d]) {
            ans.push_back({u});
            for (int i = d - 1; i; i--) {
                for (int v : a[i]) {
                    if (e[u].find(v) == e[u].end()) {
                        u = v;
                        a[i].erase(v);
                        ans.back().push_back(v);
                        break;
                    }
                }
            }
        }
    }
    cout << ans.size() << "\n";
    for (auto &i : ans) cout << i.size() << " " << i << "\n";
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    // while (c--) {
    //     vi ans = solve();
    //     if (ans.empty()) cout << "NO";
    //     else cout << "YES\n" << ans << "\n";
    // }
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}