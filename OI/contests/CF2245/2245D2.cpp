// Problem : D2. Construct an Array (Hard Version) https://codeforces.com/contest/2245/problem/D2
// Time    : 2026-09-30 09:57:49
#include <iostream>
#include <queue>
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
int n, m;
vector<vector<pii>> e;
vector<vi> t;
vi a, vis, in, ans;

using std::queue;

vi solve() {
    cin >> n >> m;
    assign(n + 1, e, a, vis, t, in, ans);
    queue<int> q;
    struct Input {
        int op, u, v;
    };
    vector<Input> inputs;
    while (m--) {
        int op, u, v;
        cin >> op >> u >> v;
        inputs.push_back({op, u, v});
        if (u == v) {
            a[u] = op;
            q.push(u);
            continue;
        }
        e[u].push_back({v, op});
        e[v].push_back({u, op});
    }
    for (int i = 0; i <= n; i++) {
        int k = 1;
        label:
        if (i && !a[i]) {
            q.push(i);
            a[i] = k;
        }
        vi changed = i ? vi{i} : vi{};
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (const auto &[v, w] : e[u]) {
                if (a[v]) {
                    if (a[u] == a[v] && a[u] != w) {
                        if (i && k == 1) {
                            k++;
                            q = {};
                            for (int x : changed) {
                                vis[x] = 0;
                                a[x] = 0;
                            }
                            goto label;
                        } else return {};
                    }
                    continue;
                } 
                if (w != a[u] && !vis[v]) {
                    changed.push_back(v);
                    a[v] = w;
                    q.push(v);
                }
            }
        }
    }
    for (const auto &[op, u, v] : inputs) {
        if (a[u] == a[v] && a[u] != op) 
            return {};
        if (u != v && a[u] != a[v]) {
            if (a[u] == op) t[v].push_back(u);
            else t[u].push_back(v);
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int v : t[u]) in[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i);
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[u] = ++cnt;
        if (a[u] == 2) ans[u] = - ans[u];
        for (int v : t[u]) {
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
    if (cnt < n) return {};
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    // while (c--) solve();
    while (c--) {
        auto res = solve();
        if (res.empty()) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 1; i <= n; i++) {
                cout << res[i] << " ";
            }
            cout << "\n";
        }
    }
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}