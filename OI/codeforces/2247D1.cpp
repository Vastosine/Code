// Problem : D1. XOR Sorting (Easy Version) https://codeforces.com/problemset/problem/2247/D1
// Time    : 2026-10-09 11:29:44
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
    int n, q;
    cin >> n >> q;
    vi a(n);
    cin >> a;
    vector<pii> b(n);
    for (int i = 0; i < n; i++) b[i] = {a[i], i};
    sort(b);
    // for (auto &[x, i] : b) cout << x << " " << i << "\n";
    int K = 1;
    for (int i = 0; i < n; i++) K &= i == b[i].second;
    if (K) return 0;
    for (int k = 1; (1 << (k - 1)) < n; k++) {
        K = 1;
        for (int i = 0; i < n; i++) {
            K &= ((i ^ b[i].second) >> k << k) < (1 << (k - 1)); 
        }
        if (K) return (1 << (k - 1));
    }
    return 0;
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