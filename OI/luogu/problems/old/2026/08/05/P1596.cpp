// Problem : P1596 [USACO10OCT] Lake Counting S https://www.luogu.com.cn/problem/P1596
// Time    : 2026-08-05 09:23:55

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
#define F(f, x) (f)[(x).first][(x).second]
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename A, typename B> std::istream &operator>>(std::istream &in, std::pair<A, B> &x) { return in >> x.first >> x.second; }
bool available(const pii &x, int n, int m) { return x.first > 0 && x.second > 0 && x.first <= n && x.second <= m; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

int n, m, cnt;
vector<vi> a, f;

void dfs(int x, int y, int z) {
    if (f[x][y]) return;
    if (a[x][y]) return;
    f[x][y] = z;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (!available({x + i, y + j}, n, m) || f[x + i][y + j]) continue;
            dfs(x + i, y + j, z);
        }
    }
}

void solve() {
    cin >> n >> m;
    a.assign(n + 1, vi(m + 1));
    f.assign(n + 1, vi(m + 1));
    for (int i = 1; i <= n; i++) {
        std::string s;
        cin >> s;
        for (int j = 1; j <= m; j++) a[i][j] = s[j - 1] == '.';
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (f[i][j] || a[i][j]) continue;
            cnt++;
            dfs(i, j, cnt);
        }
    }
    cout << cnt;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}