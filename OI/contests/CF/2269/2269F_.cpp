// Problem : F. AghaBalaSar and Hamed https://codeforces.com/contest/2269/problem/F
// Time    : 2026-09-26 22:38:54
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
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

int check(const vi &a, int i, int j) {
    int n = a.size();
    int ans = 0;
    for (int k = i; k < n && i < j; k++) {
        if (a[k] > a[i]) {
            i = k;
            ans++;
        }
    }
    return i < j ? 0 : ans + (i > j);
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans += check(a, i, j);
        }
    }
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}