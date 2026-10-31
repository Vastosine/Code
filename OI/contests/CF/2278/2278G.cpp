// Problem : G. 0s and 1s https://codeforces.com/contest/2278/problem/G
// Time    : 2026-10-31 22:41:32
#include <iostream>
#include <vector>
#include <algorithm>
#define cautor const auto &
#define autor auto &
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

const int M = 998244353;
vector<ll> pow2;

void init() {
    int n = 2e5 + 5;
    pow2.assign(n, 1);
    for (int i = 1; i < n; i++) {
        pow2[i] = pow2[i - 1] * 2 % M;
    }
}

int n;
vector<vi> e, fl;
vi a, b, dep;

void build(int u = 1, int d = 1) {
    dep[u] = d;
    fl[d].push_back(u);
    for (cautor v : e[u]) {
        if (!dep[v]) build(v, d + 1);
    }
}

auto Main([[maybe_unused]] int C = 0) {
    cin >> n;
    assign(n + 1, e, dep, fl);
    a.assign(1, 0);
    b.assign(1, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    string s1, s2;
    cin >> s1 >> s2;
    for (cautor i : s1) a.push_back(i - '0');
    for (cautor i : s2) b.push_back(i - '0');
    build();
    ll ans = 0;
    for (int d = 1; d <= n && !fl[d].empty(); d++) {
        vi c(2);
        for (int u : fl[d]) {
            if (a[u] > 1) {
                for (int v : e[u]) a[v] += a[u] / 2;
                a[u] %= 2;
            }
            c[a[u] ^ b[u]]++;
        }
        if (c[0] && c[1]) return -1ll;
        if (c[1]) {
            (ans += pow2[d - 1]) %= M;
            for (int u : fl[d]) {
                a[u]++;
                if (a[u] > 1) {
                    for (int v : e[u]) a[v] += a[u] / 2;
                    a[u] %= 2;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
