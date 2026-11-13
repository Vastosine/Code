// Problem : P4016 负载平衡问题 https://www.luogu.com.cn/problem/P4016
// Time    : 2026-11-12 22:20:05
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

const int inf = 1 << 30;

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    int s = 0, t = n + 1, N = n + 2;
    vector<vi> e(N);
    vi to, c, dep, cur, w, dis, pre;
    int sum = 0;
    auto addEdge = [&] (int u, int v, int cap, int cost) {
        e[u].push_back(to.size());
        to.push_back(v);
        c.push_back(cap);
        w.push_back(cost);
        e[v].push_back(to.size());
        to.push_back(u);
        c.push_back(0);
        w.push_back(-cost);
    };
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        addEdge(s, i, x, 0);
        sum += x;
    }
    for (int i = 1; i <= n; i++) {
        addEdge(i, t, sum / n, 0);
    }
    for (int i = 1; i <= n; i++) {
        addEdge(i, i % n + 1, inf, 1);
        addEdge(i % n + 1, i, inf, 1);
    }

    auto SPFA = [&] (int s) {
        dis.assign(N, inf);
        vi cnt(N), inq(N);
        pre.assign(N, 0);
        queue<int> q;
        dis[s] = 0; q.push(s); inq[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i : e[u]) {
                if (int v = to[i], nd = dis[u] + w[i]; c[i] && nd < dis[v]) {
                    dis[v] = nd;
                    pre[v] = i;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= N) return false;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        return true;
    };

    auto Dinic = [&] (int s, int t) {
        int cost = 0;
        while (true) {
            // assign(N, dep, cur);
            // dep[s] = 1;
            // vi o(1, s);
            // for (int i = 0; i < (int) o.size(); i++) {
            //     int u = o[i];
            //     for (int j : e[u]) {
            //         int v = to[j];
            //         if (!dep[v] && c[j]) dep[v] = dep[u] + 1, o.push_back(v);
            //     }
            // }
            // if (!dep[t]) return cost;
            // auto dfs = [&] (auto &&f, int u, int lim = inf) {
            //     if (!lim || u == t) return lim;
            //     int ret = 0;
            //     for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
            //         int i = e[u][cur[u]];
            //         if (dep[to[i]] == dep[u] + 1) {
            //             int add = f(f, to[i], min(c[i], lim - ret));
            //             ret += add;
            //             c[i] -= add;
            //             c[i ^ 1] += add;
            //         }
            //     }
            //     return ret;
            // };
            // ans += dfs(dfs, s);
            while (true) {
                if (!SPFA(s)) return cerr << 1 << "\n", cost;
                if (!pre[t]) return cost;
                int lim = inf;
                for (int v = t; v != s; v = to[pre[v] ^ 1]) {
                    lim = min(lim, c[pre[v]]);
                    // cout << v << " ";
                }
                // cout << "\n" << lim << "\n\n";
                if (!lim) break;
                for (int v = t; v != s; v = to[pre[v] ^ 1]) {
                    c[pre[v] ^ 1] += lim;
                    c[pre[v]] -= lim;
                    cost += lim * w[pre[v]];
                }
            }
        }
    };
    return Dinic(s, t);
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
