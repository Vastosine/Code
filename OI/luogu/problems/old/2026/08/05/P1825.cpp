// Problem : P1825 [USACO11OPEN] Corn Maze S https://www.luogu.com.cn/problem/P1825
// Time    : 2026-08-05 09:23:58

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
#define F(f, x) (f)[(x).first][(x).second]
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename A, typename B> std::istream &operator>>(std::istream &in, std::pair<A, B> &x) { return in >> x.first >> x.second; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

vector<vi> a, vis, dis;
vector<vector<pii>> f, tp(26);
pii st;

void solve() {
    int n, m;
    cin >> n >> m;
    a.assign(n + 2, vi(m + 2, -1));
    vis.assign(n + 2, vi(m + 2, 0));
    dis.assign(n + 2, vi(m + 2, -1));
    f.assign(n + 2, vector<pii>(m + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c != '#') a[i][j] = 0;
            if (c >= 'A' && c <= 'Z') {
                tp[c - 'A'].push_back({i, j});
                a[i][j] = 1;
            }
            if (c == '@') st = {i, j};
            if (c == '=') a[i][j] = 2;
        }
    }
    for (const auto &i : tp) {
        if (!i.empty()) {
            F(f, i[0]) = i[1];
            F(f, i[1]) = i[0];
        }
    }
    std::queue<pii> q;
    const pii NEXT[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    q.push(st);
    F(dis, st) = 0;
    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        if (F(vis, u)) continue;
        F(vis, u) = true;
        for (pii i : NEXT) {
            pii v = i + u;
            if (F(a, v) == 1) v = F(f, v);
            if (!~F(a, v) || F(vis, v)) continue;
            if (F(a, v) == 2) {
                cout << F(dis, u) + 1;
                return;
            }
            F(dis, v) = F(dis, u) + 1;
            q.push(v);
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}