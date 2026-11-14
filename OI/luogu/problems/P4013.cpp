// Problem : P4013 数字梯形问题 https://www.luogu.com.cn/problem/P4013
// Time    : 2026-11-14 16:23:42
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

int N;                  
vector<vi> e;           
vi to, preEdge;
vll cost, dis, cap;          
vll cap0;                

void MCMF_init(int n) {
    N = n;
    e.assign(n, {});
    to.clear(), cap.clear(), cost.clear();
}

int addEdge(int u, int v, int c, ll w) {
    int id = (int)to.size();
    e[u].push_back(id);
    to.push_back(v), cap.push_back(c), cost.push_back(w);
    e[v].push_back(id + 1);
    to.push_back(u), cap.push_back(0), cost.push_back(-w);
    return id;
}

void MCMF_snapshot() { cap0 = cap; }
void MCMF_reset() { cap = cap0; }

pll MCMF(int s, int t, int dir = 1) {
    ll flow = 0, ans = 0;
    while (true) {
        dis.assign(N, INF);
        preEdge.assign(N, -1);
        vi cnt(N, 0), inq(N, 0);
        queue<int> q;

        dis[s] = 0, q.push(s), inq[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i : e[u]) {
                int v = to[i];
                if (cap[i] <= 0) continue;
                if (ll nd = dis[u] + cost[i] * dir; nd < dis[v]) {
                    dis[v] = nd;
                    preEdge[v] = i;
                    cnt[v] = cnt[u] + 1;
                    if (cnt[v] >= N) return {-1, -1}; 
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        if (preEdge[t] == -1) break;

        ll lim = INF;
        for (int v = t; v != s; v = to[preEdge[v] ^ 1]) lim = min(lim, cap[preEdge[v]]);
        for (int v = t; v != s; v = to[preEdge[v] ^ 1]) {
            cap[preEdge[v]] -= lim;
            cap[preEdge[v] ^ 1] += lim;
            ans += 1ll * lim * cost[preEdge[v]] * dir;
        }
        flow += lim;
    }
    return {flow, ans * dir}; 
}



auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    int s = 0, l = n + m - 1, t = 1, NN = 1e4;
    vector<vll> a(m + 1, vll(l + 1));
    auto f = [&] (int x, int y) {
        return x * l + y;
    };
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n + i; j++) {
            cin >> a[i][j];
        }
    }
    auto build = [&] (ll c1, ll c2) {
        MCMF_init(NN);
        for (int i = 1; i <= n; i++) addEdge(s, i * 2, 1, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 1; j <= n + i; j++) {
                int x = f(i, j);
                addEdge(x * 2, x * 2 + 1, c1, a[i][j]);
            }
        }
        for (int i = 0; i < m - 1; i++) {
            for (int j = 1; j <= n + i; j++) {
                int x = f(i, j), y = f(i + 1, j);
                addEdge(x * 2 + 1, y * 2, c2, 0);
                addEdge(x * 2 + 1, y * 2 + 2, c2, 0);
            }
        }
        for (int i = 1; i <= l; i++) addEdge(f(m - 1, i) * 2 + 1, t, n, 0);
    };
    build(1, 1);
    cout << MCMF(s, t, -1).second << "\n";
    build(n, 1);
    cout << MCMF(s, t, -1).second << "\n";
    build(n, n);
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
