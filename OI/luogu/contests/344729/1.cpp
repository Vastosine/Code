// f[L][C] = \max f[L = l[i]][c[i]] (c[i] != C)

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

const int N = 1e3 + 1;

vector<int> l(N), v(N), c(N), col(N);
int n, L;

int dfs(int x = 1, int col = 0, int len = L) {
    if (!len) return 0;
    int ans = 0x80000000;
    for (int i = x; i <= n; i++) {
        if (col == c[i] || L < v[i]) continue;
        ans = max(ans, v[i] + dfs(i + 1, c[i], len - l[i]));
    }
    return ans;
}

int c_cnt;

int main() {
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> v[i] >> col[i];
        for (int j = 1; j < i; j++) {
            if (col[i] == col[j]) {
                c[i] = c[j];
            }
        }
        if (!c[i]) c[i] = ++c_cnt;
    }
    vector<vector<int>> f(1e4, vector<int>(N, 0x80000000));
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= n; j++) {
            if (l[j] == i) f[i][j] = v[j];
            else for (int k = 1; k < j; k++) {
                if (c[j] == c[k] || i < l[j]) continue;
                f[i][j] = max(f[i][j], f[i - l[j]][k] + v[j]);
            }
            // cout << f[i][j] << " ";
        }
        // cout << "\n";
    }
    int ans = 0x80000000;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, f[L][i]);
    }
    cout << (ans > 0 ? ans : -1);
}