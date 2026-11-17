// Problem : P1433 吃奶酪 https://www.luogu.com.cn/problem/P1433
// Time    : 2026-08-05 09:23:50

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int n;
vector<vector<double>> a;
vector<double> state;
vi vis;

double f(double x, double y) { return sqrt(x * x + y * y); }

int statement(int x) {
    for (int i : vis) {
        x = x * 2 + i;
    }
    return x;
}

double dfs(int i = 0, int x = n) {
    if (i == n) return 0;
    int st = statement(x);
    if (state[st] > -1) return state[st];
    double ans = 1e9;
    for (int j = 0; j < n; j++) {
        double dis = f(a[j][0] - a[x][0], a[j][1] - a[x][1]);
        if (vis[j]) continue;
        vis[j] = true;
        ans = std::min(ans, dfs(i + 1, j) + dis);
        vis[j] = false;
    }
    return state[st] = ans;
}

void solve() {
    cin >> n;
    a.assign(n, vector<double>(2));
    vis.assign(n, 0);
    state.assign((n + 1) << n, -1);
    cin >> a;
    a.push_back({0, 0});
    // std::sort(a.begin(), a.end(), [](auto x, auto y) {
    //     return f(x[0], x[1]) < f(y[0], y[1]);
    // });
    cout << std::fixed << std::setprecision(2) << dfs();
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    std::cerr << clock() * 1.0 / CLOCKS_PER_SEC;
    return 0;
}