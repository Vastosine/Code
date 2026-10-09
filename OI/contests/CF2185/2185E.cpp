// Problem : E. The Robotic Rush https://codeforces.com/contest/2185/problem/E
// Time    : 2026-10-08 12:06:25
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
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
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

auto solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vi a(n), b(m);
    string s;
    cin >> a >> b >> s;
    sort(b);
    std::map<int, int> p;
    p[0] = 0;
    for (int i = 0, x = 0; i < k; i++) {
        x += s[i] == 'L' ? -1 : 1;
        if (p.find(x) == p.end()) p[x] = i;
    }
    vi ans(k);
    ans[0] = n;
    for (int i = 0; i < n; i++) {
        int r = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin(), l = r - 1;
        int x = k;
        if (l >= 0 && l < m) {
            auto it = p.find(b[l] - a[i]);
            if (it != p.end()) x = it->second;
        }
        if (r >= 0 && r < m) {
            if (b[r] == a[i]) {
                ans[0]--;
                continue;
            }
            auto it = p.find(b[r] - a[i]);
            if (it != p.end()) x = std::min(x, it->second);
        }
        if (x < k) ans[x]--;
    }
    for (int i = 1; i < k; i++) ans[i] += ans[i - 1];
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}