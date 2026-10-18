// Problem : D. What a SauSaGe! It's All Meat https://codeforces.com/contest/2269/problem/D
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

bool f(int x) {
    return x % 3 == 0 || x % 5 == 0;
}

int f(const vi &a) {
    int ans = 0;
    for (int i : a) {
        ans += f(i);
    }
    return ans;
}

void solve() {
    int n, q, ans;
    cin >> n >> q;
    vi a(n);
    cin >> a;
    cout << (ans = f(a)) << " ";
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        ans += f(y) - f(a[x]);
        a[x] = y;
        cout << ans << " ";
    }
    cout << "\n";
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