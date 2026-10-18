// Problem : D1. Construct an Array (Easy Version) https://codeforces.com/contest/2245/problem/D1
// Time    : 2026-09-30 09:57:49
#include <iostream>
#include <queue>
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
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vi> a(n + 1, vi(n + 1)), e(n + 1);
    while (m--) {
        int x, y, z;
        cin >> z >> x >> y;
        a[x][y] = a[y][x] = z;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i][i] == a[j][j]) {
                if (a[i][i] != a[i][j]) return cout << "NO\n", void();
            } else {
                if (a[i][i] == a[i][j]) e[j].push_back(i);
                else e[i].push_back(j);
            }
        }
    }
    vi in(n + 1), ans(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : e[u]) {
            in[v]++;
        }
    }
    int c = 1;
    std::queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (in[u] <= 0) q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[u] = c++;
        if (a[u][u] == 2) ans[u] = -ans[u];
        for (int v : e[u]) {
            in[v]--;
            if (in[v] <= 0) q.push(v);
        }
    }
    if (c <= n) return cout << "NO\n", void();
    cout << "YES\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}