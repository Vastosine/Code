#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;


int main() {
    int a, b, n;
    while (cin >> a >> b >> n && (a || b || n)) {
        vector<int> f(1000, 0);
        vector<vector<bool>> vis(7, vector<bool>(7, false));
        f[1] = f[2] = 1;
        a %= 7;
        b %= 7;
        int T = 0;
        for (int i = 3; i < 200; i++) f[i] = (a * f[i - 1] + b * f[i - 2]) % 7;
        for (int i = 100; !vis[f[i - 1]][f[i - 2]]; i++) {
            f[i] = (a * f[i - 1] + b * f[i - 2]) % 7;
            T += vis[f[i - 1]][f[i - 2]] = true;
        }
        f[0] = f[T];
        cout << f[n % T + T * 3] << "\n";
    }
}
