// Problem : D. XOR, Expression and Two Binary Numbers https://codeforces.com/problemset/problem/2234/D
// Time    : 2026-10-10 11:31:08
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
    int n, k;
    cin >> n >> k;
    string a, b, c(n, '0');
    int x, y, z;
    x = y = z = 0;
    cin >> a >> b;
    for (int i = 0; i < n; i++) {
        c[i] = ((a[i] - '0') ^ (b[i] - '0')) + '0';
        x += a[i] - '0';
        y += b[i] - '0';
        z += c[i] - '0';
    }
    x *= n - x;
    y *= n - y;
    z *= n - z;
    int m = (1 << k) + 1;
    return m / 3 * (x + y + z) + ((m % 3) / 2) * (x + y);
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