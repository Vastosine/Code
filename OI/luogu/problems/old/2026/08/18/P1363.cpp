// Problem : P1363 幻象迷宫 https://www.luogu.com.cn/problem/P1363
// Time    : 2026-08-18 17:47:35

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

int n, m;
using std::string;
vector<string> a;

#define mod(x, y) ((x % y + y) % y)
#define F(a, x, y) a[mod(x, n)][mod(y, m)]
#define G(a, p) F(a, p.first, p.second)
#define p(x, y) (pii) {mod(x, n), mod(y, n)}

pii st;
const pii D[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<pii>> vis;

const string OUTPUT[2] = {"No", "Yes"};

const pii null = {0x7fffffff, 0x7fffffff};

bool solve() {
    a.assign(n, "");
    vis.assign(n, vector<pii>(m, null));
    cin >> a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') st = {i, j};
        }
    }
    std::queue<pii> q;
    q.push(st);
    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        if (G(vis, u) != null) {
            if (G(vis, u) != u) return true;
            continue;
        }
        G(vis, u) = u;
        for (pii i : D) {
            pii v = i + u;
            if (G(a, v) != '#') {
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    while (cin >> n >> m) cout << OUTPUT[solve()] << "\n";
    return 0;
}