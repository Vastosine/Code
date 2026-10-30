// Problem : P17813 [ICPC 2019 Nanchang R] Summon https://www.luogu.com.cn/problem/P17813
// Time    : 2026-10-30 11:08:43
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

int mp(const vi &a) {
    int ans = 0;
    for (int i : a) ans = ans * 4 + i;
    return ans;
}

const int M = 998244353;

struct Matric {
    using vec = vector<ll>;
    vector<vec> a;
    int n;
    Matric(bool zero = true, int n = 64) : n(n) {
        a.assign(n, vec(n));
        if (zero) return;
        for (int i = 0; i < n; i++) a[i][i] = 1;
    }

    vec operator[](int x) const { return a[x]; }
    vec &operator[](int x) { return a[x]; }
    
    Matric operator*(const Matric &b) const {
        Matric ans(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans[i][j] += a[i][k] * b[k][j] % M) %= M;
                }
            }
        }
        return ans;
    }

    ll get() {
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            (ans += a[i][i]) %= M;
        }
        return ans;
    }

    Matric operator*=(const Matric &b) { return *this = *this * b; }
};

int phi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        ans = ans / i * (i - 1);
        while (x % i == 0) x /= i;
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans;
}

ll qpow(ll x, ll n) {
    return (n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) : 1) % M;
}

ll inv(int x) {
    return qpow(x, M - 2);
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> restrict(m, vi(4));
    cin >> restrict;
    vi res(256);
    for (auto &i : restrict) {
        int x = mp(i); 
        res[x] = 1;
    }
    Matric T;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 4; j++) {
            int nxt = i * 4 + j;
            if (res[nxt]) continue;
            nxt %= 64;
            T[i][nxt] = 1;
        }
        // for (int j = 0; j < 64; j++) cout << T[i][j] << " ";
        // cout << "\n";
    }
    vector<Matric> Tp(20);
    Tp[0] = T;
    for (int i = 1; i < 20; i++) {
        Tp[i] = Tp[i - 1] * Tp[i - 1];
        // for (auto &j : Tp[i].a) {
        //     for (int x : j) cout << x << " ";
        //     cout << "\n";
        // }
    }
    auto f = [&](int n) {
        Matric ans(0);
        for (int k = 0; k < 20; k++) {
            int x = 1 << k;
            if (x > n) break;
            if (x & n) ans *= Tp[k];
        }
        return ans;
    };
    ll ans = 0;
    for (int d = 1; d <= n; d++) {
        if (n % d) continue;
        (ans += phi(n / d) * f(d).get() % M) %= M;
    }
    return ans * inv(n) % M;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
