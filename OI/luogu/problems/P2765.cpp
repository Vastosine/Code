// Problem : P2765 魔术球问题 https://www.luogu.com.cn/problem/P2765
// Time    : 2026-11-14 14:09:27
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    int s = 0, t = 1;
    vector<vi> e(2);
    vi to, c, dep, cur, ans;
    auto addEdge = [&] (int u, int v, int w) {
        auto add = [&] (int u, int v, int w) {
            e[u].push_back(to.size());
            to.push_back(v);
            c.push_back(w);
        };
        add(u, v, w);
        add(v, u, 0);
    };
    auto Dinic = [&] (int s, int t) {
        int ans = 0;
        while (true) {
            assign(e.size(), dep, cur);
            dep[s] = 1;
            vi o(1, s);
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (int v = to[j]; !dep[v] && c[j]) dep[v] = dep[u] + 1, o.push_back(v); 
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, int lim = 1 << 30) {
                if (!lim || u == t) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    if (int i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1) {
                        int add = f(f, v, min(lim - ret, c[i]));
                        ret += add;
                        c[i] -= add;
                        c[i ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    };
    for (int k = 1, cnt = 0, st = 2; ; k++) {
        e.push_back({});
        e.push_back({});
        addEdge(s, k * 2, 1);
        addEdge(k * 2 + 1, t, 1);
        while (st * st <= k) st++;
        for (int u = st; u * u < k * 2; u++) {
            addEdge((u * u - k) * 2, k * 2 + 1, 1);
        }
        if (k - (cnt += Dinic(s, t)) > n) break;
        ans = c;
    }
    int m = e.size() / 2 - 2;
    cout << m << "\n";
    vi in(m + 1), nxt(m + 1);
    for (int u = 1; u <= m; u++) {
        for (int i : e[u * 2 + 1]) {
            if (int v = to[i] / 2; v >= 1 && v <= m && ans[i]) {
                nxt[v] = u;
                in[u] = 1;
            } 
        }
    }
    for (int st = 1; st <= m; st++) {
        if (!in[st]) {
            for (int u = st; u; u = nxt[u]) {
                cout << u << " ";
            }
            cout << "\n";
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
