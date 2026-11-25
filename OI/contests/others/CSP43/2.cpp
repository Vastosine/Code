#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
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

ll getdouble(const string &s, ll scale = 1, int b = 0) {
    ll x, y;
    char t[10];
    sscanf(s.c_str(), "%lld.%s", &x, t);
    t[b] = 0;
    sscanf(t, "%lld", &y);
    return x * scale + y;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, q;
    string t;
    cin >> n >> m >> t;
    q = m * 10000 / getdouble(t, 1000, 3);
    q *= q;
    vi w(n), c(n);
    cin >> w;
    for (int &i : c) {
        cin >> t;
        i = getdouble(t, 10, 1);
        i *= i;
    }
    vector<vi> f(n + 1, vi(q + 1));
    // f[0][q] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= q; j++) {
            f[i + 1][j] = f[i][j];
            if (j >= c[i]) f[i + 1][j] = max(f[i + 1][j], f[i][j - c[i]] + w[i]);
        }
    }
    return *max_element(f[n].begin(), f[n].end());
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
