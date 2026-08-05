// Problem : P2404 自然数的拆分问题 https://www.luogu.com.cn/problem/P2404
// Time    : 2026-08-05 09:23:54

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vi vis;
int n;

void dfs(int x, int min = 1) {
    if (!x) {
        std::string output; 
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < vis[i]; j++) {
                output += std::to_string(i) + '+';
            }
        }
        output.pop_back();
        cout << output << "\n";
        // exit(0);
        return;
    }
    for (int i = min; i <= x && i < n; i++) {
        vis[i]++;
        dfs(x - i, i);
        vis[i]--;
    }
}

void solve() {
    cin >> n;
    vis.assign(n, 0);
    dfs(n);
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}