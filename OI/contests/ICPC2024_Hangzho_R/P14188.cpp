// Problem : P14188 [ICPC 2024 Hangzhou R] Barkley III https://www.luogu.com.cn/problem/P14188?contestId=281894
// Time    : 2026-09-20 17:30:23

#include <iostream>
#include <vector>
#include <algorithm>
#define int unsigned long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] & a[rs], z[k] = f(z[ls], z[rs])
#define pushdown a[ls] &= b[k], a[rs] &= b[k], b[ls] &= b[k], b[rs] &= b[k], b[k] = -1
    vi a, b;
    vector<vector<short>> z;
    int n;
    int f(short x, short y) { return x && y ? 2 : x + y; }
    vector<short> f(const vector<short> &x, const vector<short> &y) {
        vector<short> ans(63, 0);
        for (int i = 0; i < 63; i++) {
            ans[i] = f(x[i], y[i]);
        }
        return ans;
    }

    vector<short> get(int x) {
        vector<short> ans(63, 0);
        for (int i = 0; i < 63; i++) {
            ans[i] = x & (1 << i);
        }
        return ans;
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l - 1], z[k] = get(a[k]), void();
        build(Ls, data);
        build(Rs, data);
        update;
    }

    void modify(int k, int l, int r, int i, int x) {
        if (l == r) return a[k] = x, z[k] = get(a[k]), void();
        pushdown;
        i <= mid ? modify(Ls, i, x) : modify(Rs, i, x);
        update;
    }

    void add(int k, int l, int r, int L, int R, int x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) {
            a[k] &= x, b[k] &= x;
        }
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update;
    }

    int sum(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return -1;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return sum(Ls, L, R) & sum(Rs, L, R);
    }

    int sum(int k, int l, int r, int L, int R, int p) {
        if (l > R || L > r) return -1;
        if (l >= L && r <= R) return z[k][p];
        pushdown;
        return f(sum(Ls, L, R, p), sum(Rs, L, R, p));
    }

    int query(int k, int l, int r, int L, int R, int s = -1) {
        if (l > R || L > r) return -1;
        if (l == r) return -1;
        pushdown;
        int sl = sum(Ls, L, R) & s, sr = sum(Rs, L, R) & s;
        if (sl > sr) return sl & query(Rs, L, R, sl);
        else return sr & query(Ls, L, R, sr);
    }

    int query(int L, int R) {
        return query(1, 1, n, L, R);
    }

    SegTree(const vi &data) { 
        n = data.size();
        a.assign(n << 2, -1);
        b.assign(n << 2, -1);
        z.assign(n << 2, vector<short>(63, 0));
        build(1, 1, n, data);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi data(n);
    cin >> data;
    SegTree s(data);
    while (q--) {
        int op, l, r, i, x;
        cin >> op;
        if (op == 2) {
            cin >> i >> x;
            s.modify(1, 1, n, i, x);
        } else {
            cin >> l >> r;
            if (op == 3) cout << s.query(l, r) << "\n";
            else cin >> x, s.add(1, 1, n, l, r, x);
        }
    }
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}