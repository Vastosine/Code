// Problem : P2709 【模板】莫队 / 小 B 的询问 https://www.luogu.com.cn/problem/P2709
// Time    : 2026-11-18 16:12:44
#include <algorithm>
#include <cmath>
#include <iostream>
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

auto Main([[maybe_unused]] int C = 0) {
    int n, m, k;
    cin >> n >> m >> k;
    int L = max(1, (int) (n / sqrt(m)));
    vi a(n), c(k + 1), p(m);
    for (int i = 0; i < n; i++) {
        p[i] = i / L;
    }
    struct Q {
        int l, r, id;
        void input(int i) {
            cin >> l >> r;
            l--, r--;
            id = i;
        }
    };
    vector<Q> q(m);
    cin >> a;
    for (int i = 0; i < m; i++) q[i].input(i);
    Sort(q, [&] (const Q &x, const Q &y) {
        return p[x.l] < p[y.l] || (p[x.l] == p[y.l] && x.r < y.r);
    });
    int l = 1, r = 0;
    ll ans = 0;
    vll res(m);
    auto f = [] (ll x) { return x * x; };
    auto oper = [&] (int id, int mode) {
        int x = a[id];
        ans -= f(c[x]); 
        c[x] += mode;
        ans += f(c[x]); 
    };
    for (auto &[u, v, id] : q) {
        while (l > u) oper(--l, 1);
        while (r < v) oper(++r, 1);
        while (l < u) oper(l++, -1);
        while (r > v) oper(r--, -1);
        res[id] = ans;
    }
    for (auto &i : res) cout << i << "\n";
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
