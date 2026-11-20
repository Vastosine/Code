#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
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
    vector<vi> e(n + 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
    }
    int s, t;
    cin >> s >> t;
    vi lst, o(1, s), vis(n + 1), in(n + 1);
    vis[s] = 1;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : e[u]) {
            if (!vis[v]) vis[v] = 1, o.push_back(v);
            in[v]++;
        }
    }
    o.assign(1, s);
    vi f(n + 1, 0);
    if (s != t) f[s] = 1;
    int k = 0;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i], cnt = 0;
        for (int v : e[u]) {
            cnt++;
            in[v]--;
            if (!in[v]) o.push_back(v);
            f[v] += f[u];
        } 
        if (!cnt) {
            lst.push_back(u);
            if (u == t) k = 1;
        }
    }
    // if (s == t) f[t] = e[s].empty();
    cout << f[t] * k * (s != t) << " ";
    return (lst.size() == 1 && lst[0] == t); 
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"No", "Yes"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
