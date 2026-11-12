// Problem : $name$ $url$
// Time    : $date$ $time$
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
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

auto Main([[maybe_unused]] int _C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> a(n, vi(m)), vis = a;
    vector<vector<double>> dis(n, vector<double>(m, 1e18));
    cin >> a;
    pii s, t;
    cin >> s >> t;
    swap(s.first, s.second);
    swap(t.first, t.second);
    int A = t.second - s.second, B = s.first - t.first;
    int C = t.first * s.second - s.first * t.second;
    auto line = [&] (const pii &p) {
        return A * p.first + B * p.second + C;
    };
    auto visible = [&] (const pii &p, int mode) {
        return p.first >= 0 && p.first < n && p.second >= 0 && p.second < m &&
            (p == s || p == t || (mode ? line(p) < 0 : line(p) > 0));
    };
    #define F(a, x) a[x.first][x.second]
    const double extra = sqrt(2.0) - 1;
    auto get = [&] (const pii &u, const pii &v) -> double {
        int xy = abs(u.first - v.first) + abs(u.second - v.second);
        if (!xy) return 0;
        if (xy == 1) return F(a, v);
        if (xy == 2) return F(a, v) + extra * (F(a, v) + F(a, u));
        return 1e18;
    };
    auto Dij = [&] (int mode = 0) {
        F(dis, s) = 0;
        F(vis, s) = 0;
        F(vis, t) = 0;
        F(dis, t) = 1e18;
        priority_queue<pair<double, pii>> q;
        q.push({0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (F(vis, u)) continue;
            F(vis, u) = 1;
            for (int dx = -1; dx < 2; dx++) {
                for (int dy = -1; dy < 2; dy++) {
                    pii v = {u.first + dx, u.second + dy};
                    if (u == v || !visible(v, mode)) continue;
                    auto nd = F(dis, u) + get(u, v);
                    if (nd < F(dis, v)) {
                        F(dis, v) = nd;
                        q.push({-nd, v});
                    }
                }
            }
        }
    };
    Dij(1);
    // for (auto &i : dis) cout << i << "\n";
    double ans = F(dis, t);
    Dij(0);
    ans += F(dis, t) - F(a, t) + F(a, s);
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << fixed << setprecision(2) << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
