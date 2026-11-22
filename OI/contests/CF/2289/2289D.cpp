// Problem : D. Problem from Yuzhnouralsk https://codeforces.com/contest/2289/problem/D
// Time    : 2026-11-22 17:05:14
#include <algorithm>
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

ll MSort(vll &a) {
    int n = (int) a.size();
    if (n <= 1) return 0;
    int x = n / 2, y = n - x;
    vll p, q;
    for (int i = 0; i < x; i++) p.push_back(a[i]);
    for (int i = x; i < n; i++) q.push_back(a[i]);
    ll ret = MSort(p) + MSort(q);
    for (int i = 0, u = 0, v = 0; i < n; i++) {
        if (u == x || (v < y && q[v] < p[u])) {
            a[i] = q[v++];
            ret += x - u;
        } else a[i] = p[u++];
    }
    return ret;
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vll a(n);
    cin >> a;
    for (int i = 1; i < n; i++) a[i] += a[i - 1];
    for (ll i : a) if (i < 0) return -1ll;
    return MSort(a);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
