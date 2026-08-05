// Problem : P1135 奇怪的电梯 https://www.luogu.com.cn/problem/P1135
// Time    : $data$ 08:54:11

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n, A, B;
    cin >> n >> A >> B;
    vector<int> a(n + 1), vis(n + 1, -1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    std::queue<int> q;
    q.push(A);
    vis[A] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == B) return cout << vis[u], void();
        int v = u + a[u];
        if (v <= n && !~vis[v]) {
            vis[v] = vis[u] + 1;
            q.push(v);
        }
        v = u - a[u];
        if (v > 0 && !~vis[v]) {
            vis[v] = vis[u] + 1;
            q.push(v);
        }
    }
    cout << -1;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}