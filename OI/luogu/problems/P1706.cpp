#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

std::vector<int> ans, vis;

void f(int n, int r) {
    if (!r) {
        for (int i : ans) cout << std::setw(5) << i;
        cout << "\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            ans.push_back(i);
            f(n, r - 1);
            vis[i] = false;
            ans.pop_back();
        }
    }
}

int main() {
    int n;
    cin >> n;
    ans.reserve(n);
    vis.assign(n + 1, 0);
    f(n, n);
}