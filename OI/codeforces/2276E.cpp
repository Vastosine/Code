// Problem : E. Good Substrings https://codeforces.com/contest/2276/problem/E
// Time    : 2026-10-16 10:09:25
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
    string s;
    cin >> n >> s;
    vector<vi> nxt(n + 1, vi(10, n));
    vi pos(10, n), a(n), b(n);
    for (int i = n - 1; ~i; i--) {
        pos[s[i] - '0'] = i;
        nxt[i] = pos;
    }
    auto get = [&](int x, const vi &list) {
        for (int i : list) {
            x = nxt[x][i];
        }
        return x;
    };
    vi sum(n + 2);
    for (int i = 0; i < n; i++) {
        a[i] = get(i, {2, 0, 2, 5});
        b[i] = get(i, {2, 0, 2, 6});
    }
    for (int i = 0; i < n; i++) {
        int x = n - i;
        if (a[i] < b[i]) {
            x -= (b[i] - a[i]);
            sum[a[i] + 1]++;
            sum[b[i] + 1]--;
        }
        sum[i] += x;
        sum[i + 1] -= x + 1;
        // vi S = sum;
        // for (int j = 1; j < n; j++) sum[j] += sum[j - 1];
        // for (int j = 1; j < n; j++) sum[j] += sum[j - 1];
        // cout << sum << "\n";
        // sum = S;
    }
    for (int i = 1; i < n; i++) sum[i] += sum[i - 1];
    for (int i = 1; i < n; i++) sum[i] += sum[i - 1];
    sum.pop_back();
    sum.pop_back();
    return sum;
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