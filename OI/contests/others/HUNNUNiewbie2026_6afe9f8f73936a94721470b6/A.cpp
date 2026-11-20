// Problem : $name$ $url$
// Time    : $date$ $time$
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

int K;

ll f(ll x, ll y) { return (((x >> K) ^ (y >> K)) << K) | (x + y) % (1ll << K); }

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = f(a[ls], a[rs])
    int n;
    vll a;
    SegTree(const vll &data) : n(data.size()), a(n << 2) {
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vll &data) {
        if (l == r) return a[k] = data[l - 1], void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void set(int k, int l, int r, int i, ll x) {
        if (l == r) return a[k] = x, void();
        i <= mid ? set(Ls, i, x) : set(Rs, i, x);
        update;
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        return f(query(Ls, L, R), query(Rs, L, R));
    }
};

auto Main([[maybe_unused]] int C = 0) {
    ll n, m, a0;
    cin >> n >> m >> a0 >> K;
    SegTree s(vll(n, a0));
    ll ans = 0;
    while (m--) {
        ll op, x, y;
        cin >> op >> x >> y;
        if (op == 1) ans ^= s.query(1, 1, n, x, y);
        else s.set(1, 1, n, x, y);
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
