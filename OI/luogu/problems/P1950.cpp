// Problem : P1950 长方形 https://www.luogu.com.cn/problem/P1950
// Time    : 2026-09-01 17:31:12

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
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    cin >> a;
    struct Node {
        int w, h, sum;
    };
    vi mx(m);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        std::stack<Node> s;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '*') {
                mx[j] = 0;
                while (!s.empty()) s.pop();
                continue;
            }
            int h = ++mx[j];
            int w = 1;
            while (!s.empty() && s.top().h >= mx[j]) {
                w += s.top().w;
                s.pop();
            }
            int sum = (s.empty() ? 0 : s.top().sum) + w * h;
            s.push({w, h, sum});
            ans += sum;
        }
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