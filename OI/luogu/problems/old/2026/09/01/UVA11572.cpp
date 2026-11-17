// Problem : UVA11572 唯一的雪花 Unique Snowflakes https://www.luogu.com.cn/problem/UVA11572
// Time    : 2026-09-01 17:31:15

#include <iostream>
#include <unordered_set>
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

using std::unordered_set;

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    unordered_set<int> s;
    int ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (s.find(a[i]) != s.end()) {
            s.erase(a[j++]);
        }
        s.insert(a[i]);
        ans = std::max(ans, (int) s.size());
    }
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}