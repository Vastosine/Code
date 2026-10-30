// Problem : P17814 [ICPC 2019 Nanchang R] Tree https://www.luogu.com.cn/problem/P17814?contestId=366008
// Time    : 2026-10-30 09:27:44
#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
using namespace __gnu_pbds;
template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}
int n, k;
vector<vi> son;
vi siz, dep, val, hs;
vector<oset<pii>> s;
ll ans;

void dfs(int u = 1, int d = 1) {
    siz[u] = 1;
    dep[u] = d;
    for (int v : son[u]) {
        dfs(v, d + 1);
        siz[u] += siz[v];
        if (!hs[u] || siz[hs[u]] < siz[v]) hs[u] = v;
    }
}

void insert(int u) {
    s[val[u]].insert({dep[u], u});
    for (int v : son[u]) insert(v);
}

ll ask(int v, int d) {
    if (v < 0 || v > n || d < 0) return 0;
    return s[v].order_of_key({d + 1, 0});
}

void query(int u, int top) {
    ans += ask(2 * val[top] - val[u], k - (dep[u] - dep[top]) + dep[top]);
    for (int v : son[u]) query(v, top);
}

void clear(int u) {
    s[val[u]].erase({dep[u], u});
    for (int v : son[u]) clear(v);
}

void dfs2(int u = 1, bool keep = false) {
    for (int v : son[u]) {
        if (v != hs[u]) dfs2(v);
    }
    if (hs[u]) dfs2(hs[u], true);
    for (int v : son[u]) {
        if (v != hs[u]) {
            query(v, u);
            insert(v);
        }
    }
    if (!keep) clear(u);
    else s[val[u]].insert({dep[u], u});
}

auto Main(int C = 0) {
    cin >> n >> k;
    ans = 0;
    assign(n + 1, son, siz, dep, val, hs, s);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 2; i <= n; i++) {
        int fa;
        cin >> fa;
        son[fa].push_back(i);
    }
    dfs();
    dfs2();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    // oset<pii> ss;
    // ss.insert({1, 1});
    // cerr << ss.order_of_key({2, 0});
    for (int c = 0; c < C; c++) {
        Main(c);
        cout << ans * 2 << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
