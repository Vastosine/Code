// Problem : P2762 太空飞行计划问题 https://www.luogu.com.cn/problem/P2762
// Time    : 2026-11-16 10:10:12
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}
class Dinic {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    static constexpr ll INF = 1ll << 60;
    
    Dinic(int n) : n(n), e(n) {}

    void reassign() { clear(n); }
    void clear(int n = 0) { this->n = n; e.assign(n, {}); to.clear(); cap.clear(); }
    int addEdge(int u, int v, ll c) { add(u, v, c); add(v, u, 0); return (int) to.size() - 2; }

    // Run the Dinic, return the max flow.
    ll run(int s, int t) {
        ll ans = 0;
        while (true) {
            vi cur(n), dep = reachable(s);
            if (!~dep[t]) return ans;
            auto dfs = [&] (auto &&f, int u, ll lim = INF) {
                if (!lim || u == t) return lim;
                ll ret = 0;
                for (; cur[u] < (int) e[u].size() && ret < lim; cur[u]++) {
                    if (int i = e[u][cur[u]], v = to[i]; dep[v] == dep[u] + 1 && cap[i]) {
                        ll add = f(f, v, min(lim - ret, cap[i]));
                        ret += add;
                        cap[i] -= add;
                        cap[i ^ 1] += add;
                    }
                }
                return ret;
            };
            ans += dfs(dfs, s);
        }
    }

    ll flowOn(int id) const { return cap[id ^ 1]; }

    vi reachable(int s) const {
        vi o(1, s), dep(n, -1);
        dep[s] = 0;
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            for (int j : e[u]) {
                if (int v = to[j]; !~dep[v] && cap[j]) o.push_back(v), dep[v] = dep[u] + 1;
            }
        }
        return dep;
    }

  private:
    // Add single edge
    void add(int u, int v, ll c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    int n;
    vector<vi> e;
    vll cap;
    vi to;
};

vll getll(const string &s) {
    vll ans;
    bool end = 1;
    for (int i : s) {
        if (i < '0' || i > '9') {
            end = 1;
            continue;
        }
        if (end) end = 0, ans.push_back(0);
        (ans.back() *= 10) += i - '0';
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    int s = 0, t = n + m + 1, N = t + 1;
    ll sum = 0;
    Dinic a(N);
    for (int i = 1; i <= n; i++) {
        string str;
        while (str.empty() || str == "\r") getline(cin, str);
        vll p = getll(str);
        a.addEdge(s, i, p[0]);
        sum += p[0];
        for (int j = 1; j < (int) p.size(); j++) {
            a.addEdge(i, p[j] + n, INF);
        }
    }
    for (int i = 1; i <= m; i++) {
        ll x;
        cin >> x;
        a.addEdge(i + n, t, x);
    }
    ll ans = sum - a.run(s, t);
    vi dep = a.reachable(s);
    for (int i = 1; i <= n; i++) if (~dep[i]) cout << i << " ";
    cout << "\n";
    for (int i = 1; i <= m; i++) if (~dep[i + n]) cout << i << " ";
    cout << "\n";
    return ans;
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
