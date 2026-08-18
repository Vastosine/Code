// Problem : P1621 集合 https://www.luogu.com.cn/problem/P1621
// Time    : 2026-08-18 11:26:06

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int l, r, p;
vi pr, is, f, vis;
int getF(int u) { return f[u] = (!f[u] || f[u] == u ? u : getF(f[u])); }

void merge(int u, int v) { f[getF(v)] = getF(u); }

void solve() {
    cin >> l >> r >> p;
    is.assign(r + 1, 1);
    f.assign(r + 1, 0);
    vis.assign(r + 1, 0);
    for (int i = 2; i <= r; i++) {
        if (!is[i]) continue;
        if (i >= p) pr.push_back(i);
        if (i * i > r) continue;
        for (int j = 2; i * j <= r; j++) {
            is[i * j] = false;
        }
    }
    for (int u : pr) {
        for (int v = u * 2; v <= r; v += u) {
            merge(u, v);
        }
    }
    int ans = 0;
    for (int u = l; u <= r; u++) {
        int F = getF(u);
        if (!vis[F]) {
            vis[F] = true;
            ans++;
        }
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}