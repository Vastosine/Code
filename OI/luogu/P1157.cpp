#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

std::vector<int> ans, vis;

void f(int n, int r, int min = 1) {
    if (!r) {
        for (int i : ans) cout << std::setw(3) << i;
        cout << "\n";
        return;
    }
    for (int i = min; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            ans.push_back(i);
            f(n, r - 1, i);
            vis[i] = false;
            ans.pop_back();
        }
    }
}

int main() {
    int n, r;
    cin >> n >> r;
    ans.reserve(r);
    vis.assign(n + 1, 0);
    f(n, r);
}