// Problem : P3029 [USACO11NOV] Cow Lineup S https://www.luogu.com.cn/problem/P3029
// Time    : 2026-08-31 12:20:28

#include <iostream>
#include <set>
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

int get(const vi &a, int x) {
    return std::lower_bound(a.begin(), a.end(), x) - a.begin();
}

void solve() {
    int n;
    cin >> n;
    vector<vi> a(n, vi(2));
    std::set<int> s;
    vi b;
    cin >> a;
    sort(a);
    for (int i = 0; i < n; i++) {
        s.insert(a[i][1]);
    }
    for (int i : s) b.push_back(i);
    sort(b);
    int m = b.size(), ept = m;
    vi vis(m);
    int ans = a.back()[0] - a.front()[0];
    for (int i = 0, j = 0; j <= n; i++) {
        while (j < n && ept) {
            ept -= !(vis[get(b, a[j++][1])]++);
        }
        if (ept) break;
        ans = std::min(ans, a[j - 1][0] - a[i][0]);
        ept += !(--vis[get(b, a[i][1])]);
    }
    cout << ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}