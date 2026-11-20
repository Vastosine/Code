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
    int n, m;
    cin >> n >> m;
    vector<vll> a(n + 1, vll(n + 1, INF));
    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        a[v][u] = a[u][v] = min(a[u][v], w);
    }
    int k;
    cin >> k;
    vll cost(k, INF);
    ll best = INF;
    for (int i = 0; i < k; i++) {
        int N;
        cin >> N;
        vi p(N + 2);
        vi vis(n + 1);
        for (int j = 1; j <= N; j++) cin >> p[j], vis[p[j]] = 1;
        if (N != n) continue;
        int allvis = 1;
        for (int i = 1; i <= n; i++) allvis &= vis[i];
        if (!allvis) continue;
        vis[0] = 1;
        ll dis = 0;
        for (int j = 0; j <= n; j++) {
            ll x = a[p[j]][p[j + 1]];
            if (x >= INF) {
                dis = INF;
                break;
            }
            dis += x;
        }
        cost[i] = dis;
        best = min(best, dis);
    }
    int cnt = 0, pos = -1;
    for (int i = 0; i < k; i++) {
        if (cost[i] == best) {
            if (!~pos) pos = i;
        }
        if (cost[i] < INF) cnt++;
    }
    cout << cnt << "\n" << pos + 1 << " " << best;
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
