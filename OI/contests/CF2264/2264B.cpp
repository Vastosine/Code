// Problem : B. Knife's Pill Farm https://codeforces.com/contest/2264/problem/B
// Time    : 2026-09-21 10:28:34

#include <iostream>
#include <set>
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

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1);
    std::multiset<int> s;
    int ans = 0x8000000000000000;
    for (int i = 1, sum = 0; i <= n; i++) {
        cin >> a[i];
        if (i >= m) {
            ans = std::max(ans, a[i] * m - sum);
        }
        s.insert(a[i]);
        sum += a[i];
        if (i >= m) {
            auto it = s.end();
            it--;
            sum -= *it;
            s.erase(it);
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