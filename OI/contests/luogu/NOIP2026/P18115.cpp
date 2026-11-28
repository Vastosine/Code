// Problem : P18115 [NOIP2026] 和弦 / chord（民间数据） https://www.luogu.com.cn/problem/P18115?contestId=376524
// Time    : 2026-11-28 17:20:35
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? " " : "") << a[i]; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<vector<T>> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? "\n" : "") << a[i]; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename T> void Unique(vector<T> &a) { sort(a.begin(), a.end()), a.erase(unique(a.begin(), a.end()), a.end()); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

szt f(szt n, szt x) {
    while (n % x && x * x <= n) x++;
    if (n % x == 0) return x;
    for (szt p = n / x; p; p--) {
        if (n % p == 0) return n / p;
    }
    return n;
}

auto Main(int = 0) {
    szt x, y;
    cin >> x >> y;
    if (x > y) swap(x, y);
    szt z = y - x;
    if (!z || y % z == 0) return lcm(x, y);
    if (z > x) z = f(z, x);
    szt p = x / z, q = y / z;
    return min(lcm(x, y), lcm(p + 1, q + 1) * z);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
