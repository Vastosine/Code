// Problem : T812405 [ICPC 2026 Nanchang I] Legacy Code https://www.luogu.com.cn/problem/T812405?contestId=372198
// Time    : 2026-11-19 13:00:05
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
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

const int M = 998244353;

template <typename T>
void G(T &x) {
    if (x) {
        x %= (M - 1);
        if (!x) x = M - 1;
    }
}

struct Matric {
    int n, m;
    vector<vll> a;
    Matric(int n = 0, int m = 0) : n(n), m(m), a(n, vll(m)) {}

    static Matric identity(int n) {
        Matric a(n, n);
        for (int i = 0; i < n; i++) a[i][i] = 1;
        return a;
    }

    void input() {
        // cin >> n >> m;
        // a.assign(n, vi(m));
        cin >> a;
    }

    vll &operator[](int x) { return a[x]; }
    const vll &operator[](int x) const { return a[x]; }

    Matric operator*(const Matric &b) const {
        if (m != b.n) return {};
        Matric ans(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                __int128 s = 0;
                for (int k = 0; k < m; k++) {
                    // G(ans[i][j] += a[i][k] * b[k][j]);
                    s += a[i][k] * b[k][j];
                }
                G(s);
                ans[i][j] = s;
            }
        }
        return ans;
    }

    int size() const { return a.size(); }
};

ll qpow(ll x, ll n) {
    x = (x % M + M) % M;
    ll r = 1;
    while (n) { if (n & 1) r = r * x % M; x = x * x % M; n >>= 1; }
    return r;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, q;
    cin >> n >> m >> q;
    Matric ID = Matric::identity(n), a = ID;
    while (m--) {
        int x, u, v;
        cin >> x >> u >> v;
        x--;
        u--;
        v--;
        for (int i = 0; i < n; i++) {
            G(a[x][i] = a[u][i] + a[v][i]);
        }
        // for (auto &i : a.a) {
        //     cout << i << "\n";
        // }
        // cout << "\n";
    }
    const int B = 20, L = 8;
    vector<vector<Matric>> F(L + 1, vector<Matric>(B));
    F[0][1] = a;
    for (int i = 0; i <= L; i++) {
        F[i][0] = ID;
        if (i) F[i][1] = F[i - 1].back() * F[i - 1][1];
        for (int j = 2; j < B; j++) {
            F[i][j] = F[i][j - 1] * F[i][1];
        }
    }
    auto mul = [&] (const Matric &a, const vll &b) {
        vll ans(n);
        for (int i = 0; i < n; i++) {
            ll res = 1;
            for (int j = 0; j < n && res; j++) {
                if (a[i][j]) (res *= qpow(b[j], a[i][j])) %= M;
            }
            ans[i] = res;
        }  
        return ans;
    };
    auto qp = [&] (ll n, vll &v) {
        for (int i = 0; n; i++, n /= B) {
            if (n % B) v = mul(F[i][n % B], v);
        }
    };
    while (q--) {
        vll x(n);
        int k;
        cin >> k >> x;
        qp(k, x);
        // Matric b = a;
        // for (int i = 1; i < k; i++) b = b * a;
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }        
        cout << "\n";
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
