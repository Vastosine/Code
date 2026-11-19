// Problem : P17897 [ICPC 2026 Nanchang I] Journey of GCD https://www.luogu.com.cn/problem/P17897?contestId=372198
// Time    : 2026-11-19 18:41:53
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

vector<vi> e;
int n;

auto Main([[maybe_unused]] int C = 0) {
    int N, m;
    cin >> N >> m;
    vi a(N), ans(m);
    cin >> a;
    n = *max_element(a.begin(), a.end());
    vector<pii> q(m);
    vector<vi> p(n + 1);
    cin >> q;
    for (int i = 0; i < m; i++) {
        auto &[u, v] = q[i];
        u = a[u - 1], v = a[v - 1];
        if (u == v) {
            ans[i] = u;
            continue;
        }
        p[u].push_back(i);
        p[v].push_back(i);
    }
    e.assign(n + 1, {});
    vi has(n + 1), fa(n + 1);
    auto getF = [&] (auto &&f, int u) -> int {
        return fa[u] = fa[u] ? fa[u] == u ? u : f(f, fa[u]) : u;
    }; 
    for (int x : a) has[x] = 1;
    for (int i = n; i; i--) {
        auto merge = [&] (int u, int v) {
            int fu = getF(getF, u), fv = getF(getF, v);
            if (fu == fv) return false;
            if (p[fv].size() > p[fu].size()) swap(fu, fv);
            fa[fv] = fu;
            for (int id : p[fv]) {
                if (auto &[x, y] = q[id]; !ans[id] && getF(getF, x) == getF(getF, y)) {
                    ans[id] = i;
                }
                if (!ans[id]) p[fu].push_back(id);
            }
            return true;
        };
        vi lst;
        for (int j = i; j <= n; j += i) {
            if (has[j]) lst.push_back(j);
        }
        for (int j = 1; j < (int) lst.size(); j++) {
            if (int u = lst[j], v = lst[j - 1]; merge(u, v)) {
                e[u].push_back(v);
                e[v].push_back(u);
                // cout << u << " " << v << "\n";
            }
        }
        // for (int u : lst) {
        //     for (int id : p[u]) {
        //         if (auto &[x, y] = q[id]; !ans[id] && getF(getF, x) == getF(getF, y)) {
        //             ans[id] = i;
        //         }
        //     }
        // }
    }
    for (int x : ans) cout << x << "\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ns << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
