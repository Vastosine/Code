// Problem : P1347 [ECNA 2001] 排序 https://www.luogu.com.cn/problem/P1347
// Time    : 2026-08-18 17:47:36

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::queue;

int n, m;
vector<vi> e;
vi ans;

int check(vi in) {
    queue<int> q;
    ans.clear();
    for (int i = 0; i < n; i++) {
        if (!in[i]) q.push(i);
    }
    int t = 0, k = true;
    while (!q.empty()) {
        if (q.size() > 1) k = false;
        int u = q.front();
        q.pop();
        t++;
        ans.push_back(u);
        for (int v : e[u]) {
            if (!in[v]) continue;
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
    if (t < n) return -1;
    return k;
}

vi vis;

void solve() {
    cin >> n >> m;
    vi in(n);
    e.assign(n, {});
    vis.assign(n, {});
    for (int i = 1; i <= m; i++) {
        char u, op, v;
        cin >> u >> op >> v;
        u -= 'A', v -= 'A';
        if (op == '>') std::swap(u, v);
        e[u].push_back(v);
        in[v]++;
        int k = check(in);
        if (k == -1) return cout << "Inconsistency found after " << i << " relations.", void();
        if (k) {
            cout << "Sorted sequence determined after " << i << " relations: ";
            for (char j : ans) cout << char(j + 'A');
            cout << ".";
            return;
        }
    }
    cout << "Sorted sequence cannot be determined.";
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}