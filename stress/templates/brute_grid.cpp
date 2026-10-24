// Brute force template: GRID / GRAPH DFS
//
// Use when the input is a board (n x m) or a small graph:
//   - connected components / flood fill
//   - "walk from A to B", best path with backtracking
//   - count shapes, check reachability
//
// Two patterns below: (A) component counting / flood fill, (B) backtracking path.
// For n, m <= 6 a full path DFS is fine; for bigger boards only flood fill is.
//
// Copy this file to ..\brute.cpp and edit the marked places.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int n, m;
vector<string> g;
vector<vector<int>> vis;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

bool inside(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }

// ---- EDIT: which cells can be entered --------------------------------
bool canGo(int x, int y) { return inside(x, y) && g[x][y] == '.'; }

auto solve() {
    cin >> n >> m;
    g.assign(n, "");
    for (int i = 0; i < n; i++) cin >> g[i];
    vis.assign(n, vector<int>(m, 0));

    // ---------------- (A) count connected components ------------------
    int comps = 0;
    auto flood = [&](auto &&self, int x, int y) -> void {
        vis[x][y] = 1;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (canGo(nx, ny) && !vis[nx][ny]) self(self, nx, ny);
        }
    };
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (canGo(i, j) && !vis[i][j]) { comps++; flood(flood, i, j); }
    // -----------------------------------------------------------------

    // ---------------- (B) best path with backtracking -----------------
    // ll best = NEG;
    // auto dfs = [&](auto &&self, int x, int y, int steps) -> void {
    //     best = max(best, (ll) steps);
    //     vis[x][y] = 1;
    //     for (int d = 0; d < 4; d++) {
    //         int nx = x + dx[d], ny = y + dy[d];
    //         if (canGo(nx, ny) && !vis[nx][ny]) self(self, nx, ny, steps + 1);
    //     }
    //     vis[x][y] = 0;              // undo: the neighbours may come back
    // };
    // -----------------------------------------------------------------

    return comps;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}
