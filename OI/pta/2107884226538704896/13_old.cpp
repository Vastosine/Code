#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
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

auto Main([[maybe_unused]] int C = 0) {
    int n, m, k;
    cin >> n >> m >> k;
    const int inf = 1e9;
    vector<vector<pii>> e(n + 1);
    auto addEdge = [&] (int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); };
    set<int> must;
    while (m--) {
        string s;
        while (s.empty()) getline(cin, s);
        vi a;
        s += " ";
        for (int p = 0; p < (int) s.length(); ) {
            int q = s.find_first_of(' ', p);
            // if (q == (int) string::npos) q = (int) s.length() - 1;
            int x;
            sscanf((s.substr(p, q - p) + " ").c_str(), "%d", &x);
            p = q + 1;
            a.push_back(x);
        }
        int len = (int) a.size() / 2;
        must.insert(a[0]);
        must.insert(a.back());
        for (int i = 0; i < len; i++) {
            addEdge(a[i * 2], a[i * 2 + 2], a[i * 2 + 1]);
        }
    }
    vector<vi> dis(n + 1, vi(n + 1, inf));
    for (int u = 1; u <= n; u++) {
        if (e[u].size() == 1) must.insert(u);
        dis[u][u] = 0;
        for (auto &[v, w] : e[u]) {
            dis[u][v] = min(dis[u][v], w);
        }
    }
    for (int mid = 1; mid <= n; mid++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                dis[u][v] = min(dis[u][v], dis[u][mid] + dis[mid][v]);
            }
        }
    }
    // for (int u = 1; u <= n; u++) {
    //     for (int v = 1; v <= n; v++) {
    //         cout << dis[u][v] << " ";
    //     }
    //     cout << "\n";
    // }
    int q;
    cin >> q;
    while (q--) {
        int u;
        cin >> u;
        set<int> ans;
        for (auto i : must) {
            if (dis[u][i] != inf) ans.insert(i);
        }
        map<int, set<pii>> s;
        for (int v = 1; v <= n; v++) {
            if (dis[u][v] == inf) continue;
            int d = dis[u][v] + k - 1;
            s[d / k].insert({-(d % k), v});
        }
        for (auto &[p, Q] : s) {
            auto st = Q.begin()->first;
            for (auto &[S, T] : Q) {
                if (S == st) ans.insert(T);
            }
        }
        ans.insert(u);
        for (int i : ans) cout << i << " \n"[i == *--ans.end()];
        // cout << "\n";
    }
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
