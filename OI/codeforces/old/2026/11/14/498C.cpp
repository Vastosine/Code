// Problem : C. Array and Operations https://codeforces.com/problemset/problem/498/C
// Time    : 2026-11-14 18:09:32
#include <iostream>
#include <set>
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
vector<int> primes;
vector<bool> is;
void sieve(int n) {
    is.assign(n + 1, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i);
        for (int p : primes) {
            if (1ll * i * p > n) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}   
void init() { sieve(1e5); }

class Dinic {
  public:
    using ll = long long;
    using vi = vector<int>;
    using vll = vector<ll>;
    using pll = pair<ll, ll>;
    static const ll INF = 1ll << 60;
    
    Dinic(int n) : n(n), e(n) {}

    void reassign() { clear(n); }
    void clear(int N = 0) { this->n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    void addEdge(int u, int v, ll c) { add(u, v, c); add(v, u, 0); }

    // Run the Dinic, return the max flow.
    ll run(int s, int t) {
        ll ans = 0;
        while (true) {
            vi cur(n), dep(n), o(1, s);
            dep[s] = 1;
            for (int i = 0; i < (int) o.size(); i++) {
                int u = o[i];
                for (int j : e[u]) {
                    if (int v = to[j]; !dep[v] && cap[j]) dep[v] = dep[u] + 1, o.push_back(v);
                }
            }
            if (!dep[t]) return ans;
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

    // Print some information or else;
    void print();

  private:
    // Add single edge
    void add(int u, int v, ll c) {
        e[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(c);
    };

    int n;
    vector<vi> e;
    vll cap;
    vi to;
};

int f(int x, int p) {
    int ans = 0;
    while (x % p == 0) x /= p, ans++;
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vi a(n);
    vector<pii> b(m);
    cin >> a >> b;
    int s = 0, t = n + 1, N = t + 1;
    Dinic g(N);
    for (auto &[u, v] : b) {
        if (v & 1) swap(u, v);
    }
    ll ans = 0;
    set<int> lst;
    for (int x : a) {
        for (int p : primes) {
            if (1ll * p * p > x) break;
            if (x % p == 0) lst.insert(p);
            while (x % p == 0) x /= p;
        }
        if (x > 1) lst.insert(x);
    }
    for (int p : lst) {
        g.reassign();
        for (int u = 1; u <= n; u++) {
            int cnt = f(a[u - 1], p);
            if (!cnt) continue;
            if (u & 1) g.addEdge(s, u, cnt);
            else g.addEdge(u, t, cnt);
        }
        for (auto &[u, v] : b) {
            g.addEdge(u, v, INF);
        }
        ans += g.run(s, t);
    }
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
