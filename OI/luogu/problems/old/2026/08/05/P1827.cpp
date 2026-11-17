// Problem : P1827 [USACO3.4] 美国血统 American Heritage https://www.luogu.com.cn/problem/P1827
// Time    : 2026-08-05 20:14:24

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

std::string a, b;
int vis[128];
vector<pii> tree(128);
int n;

void build(int i = 0, int l = 0, int r = n - 1) {
    int j;
    for (j = l; j < n; j++) {
        if (a[i] == b[j]) break;
    }
    if (j > l) tree[a[i]].first = a[i + 1], build(i + 1, l, j - 1);
    if (j < r) tree[a[i]].second = a[i + 1 + j - l], build(i + 1 + j - l, j + 1, r);
}

void dfs(int u = a[0]) {
    if (tree[u].first) dfs(tree[u].first);
    if (tree[u].second) dfs(tree[u].second);
    cout << (char)u;
}

void solve() {
    cin >> b >> a;
    n = b.length();
    build();
    dfs();
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}