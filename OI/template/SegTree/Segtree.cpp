#include <iostream>
#include <vector>

using namespace std;
#define ll long long

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define update a[k] = a[ls] + a[rs];
#define pushdown a[ls] += b[k] * (mid - l + 1), a[rs] += b[k] * (r - mid), b[ls] += b[k], b[rs] += b[k], b[k] = 0
    vector<ll> a, b;
    int n;
    SegTree(const vector<ll> &data) : n(data.size()) {
        a.assign(n << 2, 0);
        b.assign(n << 2, 0);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vector<ll> &data) {
        if (l == r) return a[k] = data[l - 1], void();
        build(Ls, data);
        build(Rs, data);
        update
    }

    void add(int k, int l, int r, int L, int R, ll x) {
        if (l > R || L > r) return;
        if (l >= L && r <= R) return a[k] += x * (r - l + 1), b[k] += x, void();
        pushdown;
        add(Ls, L, R, x);
        add(Rs, L, R, x);
        update
    }

    ll query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll &i : a) cin >> i;
    SegTree s(a);
    while (q--) {
        int op, l, r;
        ll x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            s.add(1, 1, n, l, r, x);
        } else cout << s.query(1, 1, n, l, r) << "\n";
    }
}

// luogu P3372 10min