// Problem : F. AghaBalaSar and Hamed https://codeforces.com/contest/2269/problem/F
// Time    : 2026-09-26 22:38:54
#include <iostream>
#include <stack>
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

vi a, L, R, dp, vis;

void solve(int l, int r) {
    dp[r] = r - l;
    int x = r;
    for (int i = r - 1; i >= l; i--) {
        while (x + 1 && (L[x] > i || !~L[x])) x--;
        cout << x << " ";
    }
    cout << "\n";
}

void solve() {
    int n;
    cin >> n;
    assign(n, -1, a, R, L);
    assign(n, vis, dp);
    cin >> a;
    std::stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[s.top()] < a[i]) {
            R[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    for (int i = n - 1; i + 1; i--) {
        if (~R[i]) L[R[i]] = i;
    }
    for (int l = 0, r = 0; r < n; l = ++r) {
        while (r + 1 < n && ~R[r]) r++;
        solve(l, r);
    }
    // for (int i : R) cout << i << " ";
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