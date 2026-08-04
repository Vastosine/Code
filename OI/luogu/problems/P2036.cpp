#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::min;

vector<int> S, B;
int n;

int dfs(int x = 0, int s = 1, int b = 0) {
    if (x == n) return abs(s - b) + (b == 0) * 1e9;
    return min(dfs(x + 1, s, b), dfs(x + 1, s * S[x], b + B[x]));
}

int main() {
    cin >> n;
    S.assign(n, 0);
    B.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> S[i] >> B[i];
    cout << dfs();
}   