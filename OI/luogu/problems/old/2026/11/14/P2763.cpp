// Problem : P2763 试题库问题 https://www.luogu.com.cn/problem/P2763
// Time    : 2026-11-14 09:20:06
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

const int inf = 1 << 30;

// problem: 1 ~ n, category: n + 1 ~ n + k, s = 0, t = n + k + 1;
// for i in [1, n] : s -- 1 -> i
// for i in [1, n], j in a[i] : i -- 1 -> j + n
// for i in [1, k], j + n -- need[j] -> t
// Dinic < sum of need[j] -> No Solution
// for u in [1, k], v in [1, n] ans u -- 1 -> v print v
auto Main([[maybe_unused]] int C = 0) {
    int k, n;
    cin >> k >> n;
    int s = 0, t = k + n + 1, N = t + 1, sum = 0;
    vector<vi> e(N);
    vi to, c, dep, cur, need(k + 1);
    auto addEdge = [&] (int u, int v, int w) {
        auto add = [&] (int u, int v, int w) {
            e[u].push_back(to.size());
            to.push_back(v);
            c.push_back(w);
        };
        add(u, v, w);
        add(v, u, 0);
    };
    for (int i = 1; i <= k; i++) {
        cin >> need[i];
        sum += need[i];
        addEdge(i + n, t, need[i]);
    }
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, 1);
        int m;
        cin >> m;
        while (m--) {
            int v;
            cin >> v;
            addEdge(i, v + n, 1);
        }
    }

    auto Dinic = [&] (int s, int t) {
        int ans = 0;
        while (true) {
            assign(N, dep, cur);
            vi o(1, s);
            dep[s] = 1;
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (int v = to[j]; c[j] && !dep[v]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, int lim = inf) {
                if (!lim || u == t) return lim;
                int ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    if (int i = e[u][cur[u]]; dep[to[i]] == dep[u] + 1) {
                        int add = f(f, to[i], min(lim - ret, c[i]));
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
    if (Dinic(s, t) < sum) cout << "No Solution!";
    else {
        for (int u = 1; u <= k; u++) {
            cout << u << ": ";
            for (int i : e[u + n]) {
                if (int v = to[i]; v >= 1 && v <= n && c[i]) {
                    cout << v << " ";
                }
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
