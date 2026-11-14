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

vll read(const string &s) {
    vll ans;
    for (char i : s) {
        if (ans.empty() || i == ' ') ans.push_back(0);
        if (i == ' ') continue;
        (ans.back() *= 10) += i - '0';
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pll>> e(n + 1);
    auto addEdge = [&] (int u, int v, ll w) {
        e[u].push_back({v, w}); e[v].push_back({u, w});
    };
    set<int> must;
    while (m--) {
        string s;
        while (s.empty()) getline(cin, s);
        auto a = read(s);
        must.insert(a[0]);
        must.insert(a.back());
        for (int i = 2; i < (int) a.size(); i += 2) {
            addEdge(a[i], a[i - 2], a[i - 1]);
        }
    }
    vector<vll> dis(n + 1, vll(n + 1, INF));
    for (int u = 1; u <= n; u++) {
        dis[u][u] = 0;
        for (auto &[v, w] : e[u]) {
            dis[u][v] = min(dis[u][v], w);
        }
    }
    for (int K = 1; K <= n; K++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][K] + dis[K][j]);
            }
        }
    }
    vector<vi> nxt(n + 1);
    for (int u = 1; u <= n; u++) {
        set<int> ans;
        ans.insert(u);
        for (int v : must) {
            if (dis[u][v] < INF) ans.insert(v);
        }
        map<ll, set<pll>> mp;
        for (int v = 1; v <= n; v++) {
            if (dis[u][v] == INF) continue;
            int d = dis[u][v];
            mp[d / k].insert({-d % k, v});
        } 
        for (auto &[T, L] : mp) {
            ll x = L.begin()->first;
            for (auto &[d, v] : L) {
                if (x == d) ans.insert(v);
            }
        }
        nxt[u] = vi(ans.begin(), ans.end());
    }
    int q;
    cin >> q;
    while (q--) {
        int st;
        cin >> st;
        vi o(1, st), in(n + 1);
        in[st] = 1;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int v : nxt[u]) {
                if (!in[v]) o.push_back(v), in[v] = 1;
            }
        }
        Sort(o);
        for (int i = 0; i < (int) o.size(); i++) {
            cout << o[i] << " \n"[i == (int) o.size() - 1];
        }
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
