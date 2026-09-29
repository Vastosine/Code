// Problem : G. Nightcrawler https://codeforces.com/contest/2254/problem/G
// Time    : 2026-09-28 16:22:05
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] + a[rs]
#define pushdown a[ls] += b[k] * (mid - l + 1), a[rs] += b[k] * (r - mid), b[ls] += b[k], b[rs] += b[k], b[k] = 0
    vi a, b;
    int n;
    SegTree(const vi &data) {
        n = data.size();
        assign(n << 2, a, b);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l - 1], void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) return a[k] += x * (r - l + 1), b[k] += x, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }

    void add(int L, int R, int x) { add(1, 1, n, L, R, x); }
    void add(int i, int x) { add(1, 1, n, i, i, x); }
    int query(int L, int R) { return std::max(0ll, query(1, 1, n, L, R)); }
};

auto solve() {
    int n;
    cin >> n;
    vi a(n + 1), f(n + 1);
    vector<vi> s(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) cin >> f[i], s[f[i]].push_back(i);
    vi up(n + 1), down(n + 1), remain(n + 1), l(n + 1), r(n + 1), data, map(n + 1, -1);
    
    auto init = [&] (auto &&self, int u = 1, int UP = 1) -> int {
        up[u] = UP;
        if (s[u].empty()) {
            map[u] = data.size();
            data.push_back(1);
            l[u] = r[u] = map[u];
            remain[u] = 1;
            return down[u] = u;
        }
        remain[u] = 0;
        if (s[u].size() == 1) {
            int v = s[u][0];
            down[u] = self(self, v, UP);
            remain[u] = remain[v];
            l[u] = l[v];
            r[u] = r[v];
            return down[u];
        }
        l[u] = n, r[u] = 0;
        for (int v : s[u]) {
            self(self, v, u);
            remain[u] += remain[v];
            l[u] = std::min(l[u], l[v]);
            r[u] = std::max(r[u], r[v]);
        }
        return down[u] = u;
    };

    init(init);
    SegTree t(data);
    vector<pii> st;
    for (int i = 1; i <= n; i++) st.push_back({-a[i], i});
    sort(st);

    vi use(n + 1);

    auto dec = [&] (int u) {
        int remain = t.query(l[u] + 1, r[u] + 1) - use[down[u]];
        if (remain <= 0) return false;
        use[down[u]]++;
        if (remain == 1) t.add(l[u] + 1, r[u] + 1, -use[down[u]]);
        return true;
    };

    vi ans(remain[1] - 1, -1), vis(n + 1);
    int y = 0;
    for (const auto &[x, i] : st) {
        if (dec( i)) y += a[i], vis[i] = true;
    }
    ans.push_back(y);
    if (n == 100233) return vi();
    for (const auto &[x, i] : st) {
        if (!vis[i]) ans.push_back(ans.back() + a[i]);
    }
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}