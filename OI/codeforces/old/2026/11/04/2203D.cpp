// Problem : D. Divisibility Game https://codeforces.com/contest/2203/problem/D
// Time    : 2026-11-04 10:07:03
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    cin >> a >> b;
    Sort(a);
    a.erase(unique(a.begin(), a.end()), a.end());
    vi va(n + m + 1), vb(n + m + 1, 1);
    ll s = 1;
    for (int x : a) {
        if (s <= n + m) s = lcm(s, x);
        if (va[x]) continue;
        for (int y = x; y <= n + m; y += x) va[y] = 1;
    }
    for (ll y = s; y <= n + m; y += s) vb[y] = 0;
    int x = 0, y = 0, z = 0;
    for (int i : b) {
        if (va[i] && vb[i]) z++;
        else {
            x += va[i];
            y += vb[i];
        }
    }
    return x > y || (x == y && (z & 1));
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"Bob", "Alice"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
// CHECK
// 1. n=1（最小规模）   样例已有
// 2. 全部相同元素 / 全 0    ok / 正整数
// 3. 边界值（最大值、-1、0）       ok
// 4. 数量为 1 的极端（单元素、单组）ok
// 5. 我假设了但题面没写的东西：____