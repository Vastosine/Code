// Problem : P2866 [USACO06NOV] Bad Hair Day S https://www.luogu.com.cn/problem/P2866
// Time    : 2026-09-01 17:31:11

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

void solve() {
    int n;;
    cin >> n;
    vi a(n);
    cin >> a;
    std::stack<int> s;
    int ans = 0;
    for (int i = n - 1; i + 1; i--) {
        while (!s.empty() && a[s.top()] < a[i]) s.pop();
        ans += s.empty() ? n - i - 1 : s.top() - i - 1;
        while (!s.empty() && a[s.top()] <= a[i]) s.pop();
        s.push(i);
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