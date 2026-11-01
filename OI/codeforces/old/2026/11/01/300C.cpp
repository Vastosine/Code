// Problem : C. Beautiful Numbers https://codeforces.com/problemset/problem/300/C
// Time    : 2026-11-01 15:02:54
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
vector<ll> F;
const int M = 1e9 + 7;
void init() {
    int n = 1e6 + 1;
    F.assign(n, 1);
    for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % M;
}

ll qpow(ll x, ll n) {
    x %= M;
    return n ? qpow(x * x % M, n / 2) * (n & 1 ? x : 1) % M : 1;
}

ll inv(ll x) {
    return qpow(x, M - 2);
}

ll CC(int n, int m) {
    if (m > n || m < 0) return 0;
    return F[n] * inv(F[m] * F[n - m] % M) % M;
}
int a[2], n;

bool check(int s) {
    while (s) {
        if (s % 10 != a[0] && s % 10 != a[1]) return false;
        s /= 10;
    }
    return true;
}

auto Main([[maybe_unused]] int C = 0) {
    cin >> a[0] >> a[1] >> n;
    if (a[1] < a[0]) swap(a[0], a[1]);
    set<int> lst;
    for (int i = 0; i < (1 << 8); i++) {
        int x = 0;
        for (int j = 0; j <= 7; j++) {
            int k = ((1 << j) & i) > 0;
            x = x * 10 + a[k];
            lst.insert(x);
        }
    }
    ll ans = 0;
    for (ll x : lst) {
        if (x < n * a[0] || x > n * a[1]) continue;
        x -= n * a[0];
        if (a[0] == a[1]) ans = (ans + 1) % M;
        else if (x % (a[1] - a[0]) == 0) ans = (ans + CC(n, x / (a[1] - a[0]))) % M;
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
