// Problem : P4014 分配问题 https://www.luogu.com.cn/problem/P4014
// Time    : 2026-11-14 15:26:18
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
const int inf = 0x3fffffff;

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    int s = 0, t = n * 2 + 1, N = t + 1;
    vector<vi> e(N);
    vi to, c, pre, w;
    auto addEdge = [&] (int u, int v, int cap, int wi) {
        auto add = [&] (int u, int v, int cap, int wi) {
            e[u].push_back(to.size());
            to.push_back(v);
            c.push_back(cap);
            w.push_back(wi);
        };
        add(u, v, cap, wi);
        add(v, u, 0, -wi);
    };
    for (int u = 1; u <= n; u++) {
        addEdge(s, u, 1, 0);
        addEdge(u + n, t, 1, 0);
        for (int v = 1; v <= n; v++) {
            int x;
            cin >> x;
            addEdge(u, v + n, 1, x);
        }
    }
    // mode = 1 or -1
    auto MCMF = [&] (int s, int t, int mode) -> pii {
        int flow = 0, cost = 0;
        while (true) {
            vi dis(N, inf), in, cnt;
            assign(N, in, cnt);
            pre.assign(N, -1);
            dis[s] = 0, in[s] = 1;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in[u] = 0;
                for (int i : e[u]) {
                    if (int nd = dis[u] + w[i] * mode, v = to[i]; c[i] && nd < dis[v]) {
                        dis[v] = nd;
                        cnt[v] = cnt[u] + 1;
                        pre[v] = i;
                        if (cnt[v] >= N) return {-1, -1};
                        if (!in[v]) in[v] = 1, q.push(v);
                    }
                }
            }
            if (!~pre[t]) return {flow, cost * mode};
            int lim = inf;
            for (int v = t; v != s; v = to[pre[v] ^ 1]) lim = min(lim, c[pre[v]]);
            for (int v = t; v != s; v = to[pre[v] ^ 1]) {
                c[pre[v]] -= lim;
                c[pre[v] ^ 1] += lim;
                cost += lim * w[pre[v]] * mode;
            }
            flow += lim;
        }
    };
    auto _c = c;
    cout << MCMF(s, t, 1).second << "\n";
    c = _c;
    cout << MCMF(s, t, -1).second << "\n";
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
