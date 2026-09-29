// Problem : B. KiaKio and Squared Numbers https://codeforces.com/contest/2269/problem/B
// Time    : 2026-09-26 22:38:54
#include <iostream>
#include <vector>
#include <algorithm>
// #define int long long
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

int sqr(int x) { return x * x; }

int get(int x) {
    int ans = 0;
    while (x) {
        ans += sqr(x % 10);
        x /= 10;
    }
    return ans;
}

int f(int x) {
    return x * (x - 1) / 2;
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    for (int i = 0; i < 1e4; i++) {
        for (int &j : a) j = get(j);
    }
    sort(a);
    int ans = 0;
    for (int l = 0, r = 0; r < n; l = ++r) {
        while (r < n - 1 && a[l] == a[r + 1]) r++;
        ans += f(r - l + 1);
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