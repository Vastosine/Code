// Problem : A. Rumb Needs a Hand https://codeforces.com/contest/2264/problem/A
// Time    : 2026-09-21 10:28:34

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

bool solve() {
    int n;
    cin >> n;
    vi a(n + 1), vis(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, l = 1, r = n; i <= n; i++) {
        if (a[i] != i && !vis[i]) {
            if (a[a[i]] != i || i < l || i > r || a[i] < l || a[i] > r) return false;
            l = std::min(a[i], i);
            r = std::max(a[i], i);
            vis[i] = vis[a[i]] = true;
        }
    }
    return true;
}

#undef int

const string OUT[2] = {"NO", "YES"};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << OUT[solve()] << "\n";
    return 0;
}