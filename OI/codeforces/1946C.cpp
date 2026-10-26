// Problem : C. Tree Cutting https://codeforces.com/problemset/problem/1946/C
// Time    : 2026-10-26 18:50:00
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

int n, k;
vector<vi> e;
vi siz;

void init(int u) {
    siz[u] = 1;
    for (int v : e[u]) {
        if (!siz[v]) {
            init(v);
            siz[u] += siz[v];
        }
    }
}

pii dfs(int u, int x) {
    if (siz[u] < x) return {0, siz[u]};
    if (siz[u] == x) return {1, 0};
    int cnt = 0, re = 1;
    for (int v : e[u]) {
        if (siz[u] < siz[v]) continue;
        auto [p, q] = dfs(v, x);
        cnt += p, re += q;
    }
    if (re >= x) cnt++, re = 0;
    return {cnt, re};
}

bool check(int x) {
    return dfs(1, x).first > k;
}

auto solve() {
    cin >> n >> k;
    assign(n + 1, e, siz);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    init(1);
    int l = 0, r = n + 1;
    while (l < r - 1) {
        int x = ((l + r) >> 1);
        if (check(x)) l = x;
        else r = x;
    }
    return l;
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