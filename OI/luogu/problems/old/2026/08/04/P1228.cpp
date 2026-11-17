#include <iostream>

using std::cin;
using std::cout;
// #define cout std::cerr

int f[16], g[4][2] = {
    {1, 1},
    {1, 0}, 
    {0, 1},
    {0, 0}
}, h[2][2] = {{0, 1}, {2, 3}};

void solve(int k, int x, int y, int dx, int dy) {
    if (k == 1) {
        int z = h[x - dx][y - dy];
        cout << dx + g[z][0] + 1 << " " << dy + g[z][1] + 1 << " " << z + 1 << "\n";
        return;
    }
    k--;
    bool X = x >= dx + f[k], Y = y >= dy + f[k];
    int z = h[X][Y];
    cout << dx + f[k] - X + 1 << " " << dy + f[k] - Y + 1 << " " << z + 1 << "\n";
    solve(k, x, y, dx + f[k] * X, dy + f[k] * Y);
    solve(k, dx + f[k] - X, dy + f[k] - !Y, dx + f[k] * !X, dy + f[k] * Y);
    solve(k, dx + f[k] - !X, dy + f[k] - Y, dx + f[k] * X, dy + f[k] * !Y);
    solve(k, dx + f[k] - X, dy + f[k] - Y, dx + f[k] * !X, dy + f[k] * !Y);
}

int main() {
    int k, x, y;
    cin >> k >> x >> y;
    f[0] = 1;
    for (int i = 1; i < 16; i++) f[i] = f[i - 1] * 2;
    solve(k, x - 1, y - 1, 0, 0);
}