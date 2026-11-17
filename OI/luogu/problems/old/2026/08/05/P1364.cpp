// Problem : P1364 医院设置 https://www.luogu.com.cn/problem/P1364
// Time    : 2026-08-05 20:14:26

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vector<int> ls, rs, v, fa;

int get_dis(int u, int last = 0, int depth = 0) {
    int d[3] = {fa[u], ls[u], rs[u]}, ans = v[u] * depth;
    for (int v : d) {
        if (!v || v == last) continue;
        ans += get_dis(v, u, depth + 1);
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    ls.assign(n + 1, 0);
    rs.assign(n + 1, 0);
    v.assign(n + 1, 0);
    fa.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> ls[i] >> rs[i];
        fa[ls[i]] = fa[rs[i]] = i;
    }
    int ans = 0x7fffffff;
    for (int u = 1; u <= n; u++) {
        ans = std::min(ans, get_dis(u));
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}