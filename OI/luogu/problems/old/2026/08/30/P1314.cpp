// Problem : P1314 [NOIP 2011 提高组] 聪明的质监员 https://www.luogu.com.cn/problem/P1314
// Time    : 2026-08-30 12:06:06

#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

vi V, W, L, R;
int n, m, s;

int abs(int x) {
    return x < 0 ? -x : x;
}

int get(int w) {
    vi u(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) {
        u[i] = u[i - 1] + (W[i] >= w);
        v[i] = v[i - 1] + (W[i] >= w) * V[i];
    }
    int y = 0;
    for (int i = 0; i < m; i++) {
        y += (u[R[i]] - u[L[i] - 1]) * (v[R[i]] - v[L[i] - 1]);
    }
    return y;
}

int f(int w) {
    return abs(s - get(w));
}

void solve() {
    cin >> n >> m >> s;
    V = vi(n + 1), W = vi(n + 1), L = vi(m), R = vi(m);
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> W[i] >> V[i];
        r = std::max(r, W[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> L[i] >> R[i];
    }
    r++;
    while (l < r - 1) {
        int w = (l + r) / 2;
        int y = get(w);
        if (y > s) l = w;
        else r = w;
    }
    // for (int i = 0; i < s; i++) {
    //     cout << get(i) << " ";
    // }
    // int ans = s;
    // for (int i = l; ; i++) {
    //     int x = s - get(i);
    //     ans = std::min(ans, abs(x));
    //     if (x > 0) break;
    // }
    // cout << ans;
    cout << std::min(f(l), f(r));
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