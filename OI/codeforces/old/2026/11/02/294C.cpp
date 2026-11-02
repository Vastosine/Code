// Problem : C. Shaass and Lights https://codeforces.com/problemset/problem/294/C
// Time    : 2026-11-02 10:31:24
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

const int M = 1e9 + 7;
vector<ll> F;
void init() {
    int n = 1000;
    F.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % M;
}

ll qpow(ll x, ll n) {
    x %= M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1; 
}

ll inv(ll x) { return qpow(x, M - 2); }

ll CC(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return F[n] * inv(F[k] * F[n - k] % M) % M;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vi a(m);
    cin >> a;
    Sort(a);
    a.push_back(n + 1);
    vi b;
    b.push_back(a[0] - 1);
    for (int i = 1; i <= m; i++) {
        b.push_back(a[i] - a[i - 1] - 1);
    }
    int s = 0;
    ll ans = 1;
    for (int x : b) s += x, (ans *= CC(s, x)) %= M;
    for (int i = 1; i < m; i++) {
        if (b[i]) (ans *= qpow(2, b[i] - 1)) %= M;
    }
    return ans;
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

// CHECK 全 on  -> 1