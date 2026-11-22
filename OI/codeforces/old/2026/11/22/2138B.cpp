// Problem : B. Antiamuny Wants to Learn Swap https://codeforces.com/problemset/problem/2138/B
// Time    : 2026-11-22 10:09:17
#include <algorithm>
#include <iostream>
#include <stack>
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
    int n, m;
    cin >> n >> m;
    vi a, f, pge, nse;
    assign(n + 1, a, f, pge, nse);
    for (int i = 1; i <= n; i++) cin >> a[i];
    stack<int> s, t;
    for (int i = 1; i <= n; i++) {
        while (!s.empty() && a[i] > a[s.top()]) s.pop();
        if (s.empty()) s.push(i);
        else pge[i] = s.top(), s.push(i);
    }
    for (int i = n; i; i--) {
        while (!t.empty() && a[i] < a[t.top()]) t.pop();
        if (t.empty()) t.push(i);
        else nse[i] = t.top(), t.push(i);
    }
    // cout << pge << "\n" << nse << "\n";
    vi b(n + 1, n + 1);
    for (int i = 1; i <= n; i++) if (pge[i] && nse[i]) b[pge[i]] = min(b[pge[i]], nse[i]);
    for (int l = n, cur = n + 1; l; l--) {
        cur = min(cur, b[l]);
        f[l] = cur - 1;
    }
    // cout << f << "\n";
    const string OUT[2] = {"NO", "YES"};
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << OUT[f[l] >= r] << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
