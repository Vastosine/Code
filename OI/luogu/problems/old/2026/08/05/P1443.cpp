// Problem : P1443 马的遍历 https://www.luogu.com.cn/problem/P1443
// Time    : $data$ 08:54:10

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

bool available(const pii &x, int n, int m) { return x.first > 0 && x.second > 0 && x.first <= n && x.second <= m; }

#define F(x) f[x.first][x.second]

void solve() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    std::queue<pii> q;
    q.push({x, y});
    vector<vi> f(n + 1, vi(m + 1, -1));
    f[x][y] = 0;
    const pii next[8] = {{1, 2}, {2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}};
    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        for (const pii &i : next) {
            pii v = u + i;
            if (!available(v, n, m) || ~F(v)) continue;
            F(v) = F(u) + 1;
            q.push(v);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}