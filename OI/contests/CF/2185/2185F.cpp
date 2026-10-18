// Problem : F. BattleCows https://codeforces.com/contest/2185/problem/F
// Time    : 2026-10-08 12:06:25
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
#define lm (mid - l + 1)
#define rm (r - mid)
    vi a;
    SegTree(const vi &data) {
        int n = data.size();
        a.assign(n << 2, 0);
        build(1, 1, n, data);
    }

    void build(int k, int l, int r, const vi &data) {
        if (l == r) return a[k] = data[l - 1], void();
        build(Ls, data);
        build(Rs, data);
        a[k] = a[ls] ^ a[rs];
    }

    int query(int k, int l, int r, int i, int x) {
        if (l == r) return 0;
        return i <= mid ? query(Ls, i, x) + rm * (a[rs] > (a[ls] ^ x)) : query(Rs, i, x) + lm * (a[ls] >= (a[rs] ^ x));
    }
};

auto solve() {
    int n, m, N;
    cin >> n >> m;
    N = 1 << n;
    vi a(N);
    cin >> a;
    SegTree s(a);
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << s.query(1, 1, N, x, a[x - 1] ^ y) << "\n";
    }
    return 0;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}