// Problem : C. Simons and Posting Blogs https://codeforces.com/problemset/problem/2205/C
// Time    : 2026-10-16 20:18:48
#include <iostream>
#include <set>
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

using std::set;

auto solve() {
    int n;
    cin >> n;
    vector<vi> a(n);
    for (auto &i : a) {
        int m;
        cin >> m;
        i.assign(m, 0);
        for (int j = m - 1; ~j; j--) cin >> i[j];
        vi r;
        set<int> s;
        for (int j : i) if (s.find(j) == s.end()) r.push_back(j), s.insert(j);
        i = r;
    }
    vi ans;
    for (int i = 0; i < n; i++) {
        sort(a.begin() + i, a.end());
        set<int> s;
        for (int j : a[i]) ans.push_back(j), s.insert(j);
        for (int j = i + 1; j < n; j++) {
            vi replace;
            for (int k : a[j]) if (s.find(k) == s.end()) replace.push_back(k);
            a[j] = replace;
        }
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