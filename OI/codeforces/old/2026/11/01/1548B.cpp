// Problem : B. Integers Have Friends https://codeforces.com/problemset/problem/1548/B
// Time    : 2026-11-01 09:54:45
#include <iostream>
#include <numeric>
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

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
    vector<ll> a;
    int n;
    SegTree(const vector<ll> &data) : n(data.size() - 1) {
        a.assign(n << 2, 0);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vector<ll> &data) {
        if (l == r) return a[k] = data[l], void();
        build(Ls, data);
        build(Rs, data);
        a[k] = gcd(a[ls], a[rs]);
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        return gcd(query(Ls, L, R), query(Rs, L, R));
    } 
};

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;
    if (n == 1) return 1;
    for (int i = n - 1; i; i--) {
        a[i] -= a[i - 1];
        a[i] = abs(a[i]);
    }
    SegTree s(a);
    int ans = 1;
    for (int l = 1, r = 1; l < n; l++) {
        if (r < l) r = l;
        ll tmp, g = s.query(1, 1, n - 1, l, r);
        if (g == 1) continue;
        while (r < n - 1 && (tmp = gcd(g, a[r + 1])) != 1) r++, g = tmp;
        ans = max(ans, r - l + 2);
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
