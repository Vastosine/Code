#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void P3386() {
    int n, m, e;
    cin >> n >> m >> e;
    vector<vector<int>> a(n + 1), b(m + 1);
    while (e--) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    
}

int main() {
    P3386();
    return 0;
}