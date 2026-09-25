// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
// #define int long long
using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

struct SegTree {
#define ls (k << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
#define Ls ls, l, mid
#define Rs rs, mid + 1, r
#define nm (r - l + 1)
#define lm (mid - l + 1)
#define rm (r - mid)
#define update a[k] = a[ls] + a[rs];
// #define pushdown a[ls] += b[k] * lm, a[rs] += b[k] * rm, b[ls] += b[k], b[rs] += b[k], b[k] = 0
    vi a;
    SegTree(int n) {
        a.assign(n << 2, 0);
        // b.assign(n << 2, 0);
    }

    // void add(int k, int l, int r, int L, int R, int x = 1) {
    //     if (l > R || L > r) return;
    //     if (l >= L && r <= R) return a[k] += x * nm, b[k] += x, void();
    //     // pushdown;
    //     add(Ls, L, R, x);
    //     add(Rs, L, R, x);
    //     update;
    // }

    void add(int k, int l, int r, int i, int x = 1) {
        if (l == r) return a[k] += x, void();
        i <= mid ? add(Ls, i, x) : add(Rs, i, x);
    }

    int query(int k, int l, int r, int L, int R) {
        if (l > R || L > r) return 0;
        if (l >= L && r <= R) return a[k];
        // pushdown;
        return query(Ls, L, R) + query(Rs, L, R);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<pii> X(n), Y;
    vi px, py;
    for (auto &[x, y] : X) cin >> x >> y, px.push_back(x), py.push_back(y);
    for (auto &[x, y] : X) {
        x = std::lower_bound(px.begin(), px.end(), x) - px.begin();
        y = std::lower_bound(py.begin(), py.end(), y) - py.begin();
    }
    Y = X;
    sort(X);
    sort(Y, [] (auto x, auto y) { return x.second < y.second; });
    std::priority_queue<pii, vector<pii>, std::greater<>> q;
    SegTree s(n);
    vector<pii> l, r;
    for (auto &[x, y] : X) {
        if (l.empty() || l.back().first)
    }
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}