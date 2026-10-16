// Problem : $name$ $url$
// Time    : $date$ $time$
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
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
template<typename T, typename... Args> void asv(int n, T &&v, vector<Args>&... args) { (..., args.assign(n, v)); }
template<typename F, typename T, typename... Args> T &update(F &&f, T &x, Args &&...args) { return ((x = f(x, args)), ...), x; }
template<typename F, typename T, typename... Args> T func(F &&f, const T &x, Args &&...args) { T tmp(x); return ((tmp = f(tmp, args)), ...), tmp; }
using vd = vector<double>;
using vvd = vector<vd>;

double dis(const vd &x) {
    return std::sqrt(x[0] * x[0] + x[1] * x[1]);
}

double dis(const vd &x, const vd &y) {
    return dis({x[0] - y[0], x[1] - y[1]});
}

using std::min;

auto solve(int n) {
    vvd a(n, vd(2));
    cin >> a;
    sort(a);
    auto f = [&] (auto &&f, int l, int r) {
        if (r - l < 2) return 1e20;
        if (r - l == 2) return dis(a[l], a[l + 1]); 
        int mid = (l + r) >> 1;
        double d = min(f(f, l, mid), f(f, mid, r));
        vvd s;
        for (int i = l; i < r; i++) {
            if (std::abs(a[i][0] - a[mid][0]) <= d) 
                s.push_back(a[i]);
        }
        sort(s, [] (const vd &p, const vd &q) { return p[1] < q[1]; });
        int sn = s.size();
        for (int i = 0; i < sn; i++) {
            for (int j = i + 1; j < sn && s[j][1] - s[i][1] < d; j++) {
                d = min(d, dis(s[i], s[j]));
            }
        }
        return d;
    };
    return f(f, 0, n) / 2;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    while (cin >> c && c) cout << std::fixed << std::setprecision(2) << solve(c) << "\n";
    // while (c--) {
    //     vi ans = solve();
    //     if (ans.empty()) cout << "NO";
    //     else cout << "YES\n" << ans << "\n";
    // }
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}