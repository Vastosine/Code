// Problem : P5937 [CEOI 1999] Parity Game https://www.luogu.com.cn/problem/P5937
// Time    : 2026-08-31 12:20:31

#include <iostream>
#include <set>
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

vi p, f, g;

int get(int x) {
    return std::lower_bound(p.begin(), p.end(), x) - p.begin();
}

int &F(int x) {
    return f[x] = ~f[x] ? x == f[x] ? x : F(f[x]) : x;
}

int &G(int x) {
    int fa = F(x);
    return g[fa] = ~g[fa] ? F(g[fa]) : -1;
}

bool add(int u, int v, bool dif) {
    // cout << u << " " << v << " " << dif << "\n";
    bool ret = true;
    if (dif) {
        ret &= F(u) != F(v);
        (~G(u) ? f[F(G(u))] : G(u)) = F(v);
        (~G(v) ? f[F(G(v))] : G(v))= F(u);
    } else {
        ret &= !~G(u) || G(u) != F(v);
        if (~G(v)) G(u) = G(v);
        else if (~G(u)) G(v) = G(u);
        f[F(u)] = F(v);
    }
    return ret;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vi l(q), r(q), k(q);
    std::set<int> s;
    for (int i = 0; i < q; i++) {
        string str;
        cin >> l[i] >> r[i] >> str;
        k[i] = str == "odd";
        l[i]--;
        s.insert(l[i]);
        s.insert(r[i]);
    }
    for (int i : s) p.push_back(i);
    int m = p.size();
    f = g = vi(m, -1);
    for (int i = 0; i < q; i++) {
        if (!add(get(l[i]), get(r[i]), k[i])) {
            cout << i;
            return;
        }
    }
    cout << q;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}