// Problem : P2895 [USACO08FEB] Meteor Shower S https://www.luogu.com.cn/problem/P2895
// Time    : 2026-08-05 09:23:48

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
#define F(f, x) (f)[(x).first][(x).second]

const int N = 305, T = 1005;

bool available(const pii &x, int n = 301, int m = 301) { return x.first >= 0 && x.second >= 0 && x.first <= n && x.second <= m; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

void solve() {
    vector<vi> a(N, vi(N, -1)), map(N, vi(N, T));
    int n;
    cin >> n;
    const pii NEXT[5] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (n--) {
        int t, x, y;
        cin >> x >> y >> t;
        for (const pii &i : NEXT) {
            pii v = (pii){x, y} + i;
            if (available(v) && F(map, v) > t) F(map, v) = t;
        }
    }
    std::queue<pii> q;
    q.push({0, 0});
    a[0][0] = 0;
    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        if (F(map, u) == T) return cout << F(a, u), void();
        if (F(map, u) <= F(a, u)) continue;
        for (const pii &i : NEXT) {
            pii v = u + i;
            if (!available(v) || u == v || ~F(a, v)) continue;
            F(a, v) = F(a, u) + 1;
            q.push(v);
        }
    }
    cout << -1;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}