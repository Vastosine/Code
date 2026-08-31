// Problem : P3017 [USACO11MAR] Brownie Slicing G https://www.luogu.com.cn/problem/P3017
// Time    : 2026-08-30 13:03:16

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

int n, m, p, q;
vector<vi> a;

int get(int x, int y, int z, int w) {
    x--, y--;
    return a[x][y] + a[z][w] - a[x][w] - a[z][y];
}

bool check(int w, int x, int j) {
	for (int k = 0, y = 1; k < q; k++) {
        bool ans = false;
		for (int l = y; l <= m; l++) {
			if (get(x, y, j, l) >= w) {
				y = l + 1;
                ans = true;
				break;
			}
		}
        if (!ans) return false;
	}
    return true;
}
bool check(int w) {
	if (w * p * q > a[n][m]) return false;
    for (int i = 0, x = 1; i < p; i++) {
        bool ans = false;
        for (int j = x; j <= n; j++) {
            if (a[j][m] - a[x - 1][m] < w * q) continue;
            if (check(w, x, j)) {
                x = j + 1;
                ans = true;
                break;
            }
		}
        if (!ans) return false;
    }
    return true;
}

void solve() {
    cin >> n >> m >> p >> q;
    a.assign(n + 1, vi(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    int l = 0, r = a[n][m] / p / q + 1;
    // for (int i = l; i < r; i++) {
    //     int k = check(i);
    //     if (k) continue;
    //     cout << i << " ";
    // }
    while (l < r - 1) {
        int w = (l + r) / 2;
        if (check(w)) l = w;
        else r = w;
    }
    cout << l;
    std::cerr << check(l) << check(6663);
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