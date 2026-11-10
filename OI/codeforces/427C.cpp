// Problem : C. Checkposts https://codeforces.com/problemset/problem/427/C
// Time    : 2026-11-10 15:03:11
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

const int M = 1e9 + 7;
vector<vi> e;
vi a, low, dfn, col, in;
stack<int> st;
int n, cnt, c;

void dfs(int u) {
    st.push(u);
    low[u] = dfn[u] = ++cnt;
    in[u] = 1;
    for (int v : e[u]) {
        if (in[v]) {
            low[u] = min(low[u], dfn[v]);
        } else if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == dfn[u]) {
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            col[v] = c;
            in[v] = 0;
            if (u == v) break;
        }
        c++;
    }
}

// first number: SCC, choose min vertice in each
// second number: the multiple of (number of minimum value in each SCC)
auto Main([[maybe_unused]] int C = 0) {
    cin >> n;
    assign(n + 1, e, low, a, dfn, col, in);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
    }
    for (int u = 1; u <= n; u++) {
        if (!dfn[u]) dfs(u);
    }
    vll p(c, INF), q(c, 0);
    for (int u = 1; u <= n; u++) {
        if (a[u] < p[col[u]]) p[col[u]] = a[u];
    }
    for (int u = 1; u <= n; u++) {
        if (a[u] == p[col[u]]) q[col[u]]++;
    }
    ll x = 0, y = 1;
    for (ll t : p) x += t;
    for (ll t : q) (y *= t) %= M;
    cout << x << " " << y;
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
