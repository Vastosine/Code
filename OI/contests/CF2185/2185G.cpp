// Problem : G. Mixing MEXes https://codeforces.com/contest/2185/problem/G
// Time    : 2026-10-08 12:06:25
#include <iostream>
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
    int n, N = 0;
    cin >> n;
    vector<vi> a;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        N += m;
        a.push_back(vi(m));
        cin >> a.back();
        sort(a.back());
    }
    vi b(n), c(n, 1);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j : a[i]) {
            if (!k) {
                if (j > b[i]) k++;
                else c[i] = (b[i] = j + 1) + 1;
            } 
            if (k) {
                if (j > c[i]) break;
                else c[i] = j + 1;
            }
        }
        mx = std::max(mx, b[i]);
        // cout << b[i] << " " << c[i] << "\n";
    }
    vi d(mx + 1);
    for (auto &i : a) for (int j : i) if (j <= mx) d[j]++;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += b[i] * (N * (n - 1) - d[b[i]]) + c[i] * d[b[i]];
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
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}