// Problem : P1162 填涂颜色 https://www.luogu.com.cn/problem/P1162
// Time    : 2026-08-05 09:23:56

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
bool available(const pii &x, int n, int m) { return x.first >= 0 && x.second >= 0 && x.first < n && x.second < m; }
pii operator+(const pii &x, const pii &y) { return {x.first + y.first, x.second + y.second}; }

vector<vi> a, vis;
const pii NEXT[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n;

bool dfs1(const pii &u) {
    if (F(vis, u)) return false;
    F(vis, u) = true;
    bool ans = true;
    for (pii i : NEXT) {
        pii v = i + u;
        if (available(v, n, n) && !F(a, v) && !F(vis, v)) {
            ans &= dfs1(v);
        } if (!available(v, n, n)) ans = false;
    }
    return ans;
}

void dfs2(const pii &u) {
    if (F(a, u) == 2) return;
    F(a, u) = 2;
    for (pii i : NEXT) {
        pii v = i + u;
        if (!F(a, v)) {
            dfs2(v);
        }
    }
}

void solve() {
    cin >> n;
    a.assign(n, vi(n)), vis = a;
    cin >> a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!a[i][j] && dfs1({i, j})) {
                dfs2({i, j});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
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