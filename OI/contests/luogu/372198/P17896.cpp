// Problem : P17896 [ICPC 2026 Nanchang I] Gotta Go Fast https://www.luogu.com.cn/problem/P17896?contestId=372198
// Time    : 2026-11-20 10:25:18
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

void Min(ll &x, ll y) { x = min(x, y); }

auto Main([[maybe_unused]] int C = 0) {
    int n, d;
    cin >> n >> d;
    vi t(3);
    cin >> t;
    string s;
    cin >> s;
    vector<vll> f(n + 1, vll(4, INF));
    f[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            Min(f[i + 1][j], f[i][j] + t[s[i] - '0']);
            if (j < 3) Min(f[min(n, i + d)][j + 1], f[i][j]);
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << f[i] << "\n";
    // }
    return *min_element(f[n].begin(), f[n].end());
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
