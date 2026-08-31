// Problem : P1884 [USACO12FEB] Overplanting S https://www.luogu.com.cn/problem/P1884
// Time    : 2026-08-30 13:03:14

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

vector<vi> p(2), a, map;

int get(bool isY, int x) {
    return std::lower_bound(p[isY].begin(), p[isY].end(), x) - p[isY].begin() + 1;
}

int &point(int x, int y) {
    return map[get(0, x)][get(1, y)];
}

int size(bool isY, int i) {
    i--;
    return i < p[isY].size() ? p[isY][i + 1] - p[isY][i] : 0;
}

void solve() {
    int n;
    cin >> n;
    a.assign(n, vi(4)), map.assign(n * 2 + 1, vi(n * 2 + 1));
    cin >> a;
    for (vi &i : a) {
        p[0].push_back(i[0]);
        p[0].push_back(i[2]);
        p[1].push_back(i[1]);
        p[1].push_back(i[3]);
    }
    sort(p[0]);
    sort(p[1]);
    for (const vi &i : a) {
        point(i[0], i[3])++;
        point(i[2], i[1])++;
        point(i[0], i[1])--;
        point(i[2], i[3])--;
    }
    int ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            map[i][j] += map[i - 1][j] + map[i][j - 1] - map[i - 1][j - 1];
            // cout << map[i][j] << " ";
            ans += !!map[i][j] * size(0, i) * size(1, j);
        }
        // cout << "\n";
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