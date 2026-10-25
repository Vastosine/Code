// Problem : C. Edge Addeleting https://codeforces.com/contest/2277/problem/C
// Time    : 2026-10-25 14:11:57
#include <iostream>
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
    
int n, m;
vector<vi> e;
vi dis;

void dfs(int u, int d = 1) {
    if (dis[u]) return;
    dis[u] = d;
    for (int v : e[u]) {
        dfs(v, d + 1);
    }
}

auto solve() {
    cin >> n >> m;
    assign(n + 1, e, dis);
    set<int> lst;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        if (u == 1) lst.insert(v);
        else {
            e[u].push_back(v);
            e[v].push_back(u);
        }
    }
    while (m--) {
        int x;
        cin >> x;
        lst.insert(x);
    }
    dfs(n);
    int ans = 0;
    for (int i : lst) {
        ans = max(ans, dis[i]);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}