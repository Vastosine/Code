// Problem : D. Good Schedule https://codeforces.com/problemset/problem/2230/D
// Time    : 2026-10-22 12:03:00
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

auto solve() {
    int n;
    cin >> n;
    vi a(n), b(n), f(n);
    vector<pii> s;
    cin >> a >> b;
    f[0] = a[0] == b[0] || (a[0] > 1 && b[0] > 1);
    if (a[0] == b[0] && a[0] == 1) s.push_back({1, 0});
    int l = 0;
    auto find = [&] (int x) {
        return std::upper_bound(s.begin() + l, s.end(), 
            x, [&] (auto &&u, auto &&v) {
                return u > v.first;
            }
        ) - 1 - s.begin();
    };
    int ans = f[0];
    for (int i = 1; i < n; i++) {
        if (a[i] == b[i]) {
            f[i] = f[i - 1] + 1;
            if (a[i] == 1) s.push_back({1, i});
            else {
                int p = find(a[i] - 1);
                if (p >= l && p < s.size()) {
                    auto &[len, id] = s[p];
                    len++;
                    if (p > l && s[p].first >= s[p - 1].first) l = p;
                }
            }
        } else {
            vi p = {a[i], b[i]};
            sort(p);
            if (s.empty()) {
                f[i] = p[0] == 1 ? 0 : f[i - 1] + 1;
            } else if (p[0] > s[l].first + 1) {
                f[i] = f[i - 1] + 1;
            } else {
                f[i] = f[i - 1] + (p[0] > 1);
                for (int j : p) {
                    if (!f[i]) break;
                    int tmp = find(j - 1);
                    if (tmp < l || (s[tmp].first != j - 1 && j > 1)) continue;
                    auto [len, id] = s[tmp];
                    if (j == 1) id = i;
                    tmp = find(j);
                    if (tmp < l) {
                        f[i] -= f[id];
                        break;
                    }
                    f[i] -= f[id] - f[s[tmp].second];
                }
            }
        }
        ans += f[i];
    }
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
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