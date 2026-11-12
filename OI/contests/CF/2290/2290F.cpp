// Problem : F. Value Counters https://codeforces.com/contest/2290/problem/F
// Time    : 2026-11-12 22:35:23
#include <iostream>
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
void init() {}

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] + a[rs]
    int n;
    vi a;
    SegTree(int N) : n(N), a(N << 2) {}

    void modify(int k, int l, int r, int i, int x = 1) {
        if (l == r) return a[k] = x, void();
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r || L > R) return 0;
        if (l >= L && r <= R) return a[k];
        return query(Ls, L, R) + query(Rs, L, R);
    }

    void add(int i) { modify(1, 1, n, i); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
    int quein(int l, int r) { return (r - l + 1) - query(l, r); }
};

vi Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    SegTree s(n);
    auto f = [&] (int x) {
        return s.query(1, x - 1) - s.quein(x + 1, n);
    };
    auto get = [&] (int target) {
        int l = 0, r = n + 1;
        while (l < r - 1) {
            int x = (l + r) >> 1;
            int y = f(x);
            // if (y == target) return x;
            if (y < target) l = x;
            else r = x;
        }
        return r;
    };
    vi ans(n + 1);
    for (int i = 1; i <= n; i++) {
        int res = get(a[i]);
        if (!res || ans[res] || f(res) != a[i]) return {0, -1};
        ans[res] = i;
        s.add(res);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        for (int i = 1; i < (int) ans.size(); i++) cout << ans[i] << " ";
        cout << "\n";
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
