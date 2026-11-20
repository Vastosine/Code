// Problem : T812405 [ICPC 2026 Nanchang I] Legacy Code https://www.luogu.com.cn/problem/T812405?contestId=372198
// Time    : 2026-11-19 13:00:05
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
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

struct Matrix {
    int n, m;
    vector<vll> a;
    Matrix(int n = 0, int m = 0) : n(n), m(m), a(n, vll(m)) {}

    static Matrix identity(int n) {
        Matrix a(n, n);
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

    Matrix operator*(const Matrix &b) const {
        if (m != b.n) return {};
        Matrix ans(n, b.m);
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


ll qpow(ll x, ll n, int m = M) {
    x = (x % m + m) % m;
    ll res = 1;
    while (n) {
        if (n & 1) (res *= x) %= m;
        x = x * x % m;
        n >>= 1;
    }
    return res % m;
}

// m need to be prime
ll inv(ll x, int m = M) {
    return qpow(x, m - 2, m);
}

int dlog(ll g, ll h, int m) {
    int B = sqrt(m);
    unordered_map<int, int> T;
    T.reserve(B + 2);
    ll x = qpow(g, B, m);
    for (ll y = 1, i = 0; i <= B; i++, y = y * x % m) {
        T[y] = i;
    }
    ll invh = inv(g, m);
    for (ll i = 0, y = h; i < B; i++, y = y * invh % m) {
        auto it = T.find(y);
        if (it != T.end()) return i + B * it->second;
    }
    return -1;
}

struct Dlog {
    int B, steps, cap;
    vector<int> key, val;
    ll step;                       // g^{-B}
    static unsigned hs(ll y) { return (unsigned) y * 2654435761u >> 8; }

    void init(ll N) {              // N = 要取对数的总个数 = n * q
        B = (int) sqrt((double) N * (M - 1)) + 1;
        steps = (M - 1) / B + 2;
        step = inv(qpow(3, B, M), M);      // g^{-B}
        cap = 1; while (cap < 2 * B) cap <<= 1;
        key.assign(cap, 0); val.assign(cap, 0);
        ll y = 1;
        for (int j = 0; j < B; j++) {
            int pos = hs(y) & (cap - 1);
            while (key[pos]) pos = (pos + 1) & (cap - 1);
            key[pos] = (int) y + 1;   // +1 让 0 当空槽
            val[pos] = j;
            y = y * 3 % M;
        }
    }
    int operator()(ll h) const {
        ll y = h;
        for (int i = 0; i < steps; i++) {
            int pos = hs(y) & (cap - 1);
            while (key[pos]) {
                if (key[pos] == (int) y + 1) {
                    int x = i * B + val[pos];
                    if (x <= M - 2) return x;    // 溢出 M-1 的是另一个代表元，继续找
                }
                pos = (pos + 1) & (cap - 1);
            }
            y = y * step % M;
        }
        return -1;
    }
};

auto Main([[maybe_unused]] int C = 0) {
    int n, m, q;
    cin >> n >> m >> q;
    Matrix ID = Matrix::identity(n), a = ID;
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
    const int B = 2, L = 32;
    vector<vector<Matrix>> F(L + 1, vector<Matrix>(B));
    F[0][1] = a;
    for (int i = 0; i <= L; i++) {
        F[i][0] = ID;
        if (i) F[i][1] = F[i - 1].back() * F[i - 1][1];
        for (int j = 2; j < B; j++) {
            F[i][j] = F[i][j - 1] * F[i][1];
        }
    }
    Dlog dl;
    dl.init((ll) n * q);
    auto mul = [&] (const Matrix &a, const vll &b, vi &isz) {
        vll ans(n);
        vi iz(n);
        for (int i = 0; i < n; i++) {
            ll res = 0;
            for (int j = 0; j < n; j++) {
                if (a[i][j]) {
                    iz[i] |= isz[j];
                    (res += b[j] * a[i][j]) %= (M - 1);
                }
                // if (a[i][j]) (res *= qpow(b[j], a[i][j])) %= M;
            }
            ans[i] = res;
        }  
        isz = iz;
        return ans;
    };
    auto lg = [&] (ll x) { return dl(x); };
    auto qp = [&] (ll n, vll &v) {
        vi isz;
        for (ll &i : v) isz.push_back(!i), i = lg(i);
        for (int i = 0; n; i++, n /= B) {
            if (n % B) v = mul(F[i][n % B], v, isz);
        }
        for (int i = 0; i < (int) v.size(); i++) {
            if (isz[i]) v[i] = 0;
            else v[i] = qpow(3, v[i]);
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
