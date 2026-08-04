// f[L][C] = \max f[L = l[i]][c[i]] (c[i] != C)

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

const int N = 1e3 + 1;

vector<int> l(N), v(N), c(N);
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

int main() {
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> v[i] >> c[i];
    }
    int ans = dfs();
    cout << (ans > 0 ? ans : -1);
}