// Problem : P1983 [NOIP 2013 普及组] 车站分级 https://www.luogu.com.cn/problem/P1983
// Time    : 2026-08-18 17:47:37

#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
int n, m;
vector<vi> e;
vi in, dep;

void add(int u, int v) { e[u].push_back(v), in[v]++; }

void add(const vi &stops) {
    int x = e.size();
    e.push_back({});
    int st = stops.front(), ed = stops.back();
    for (int i = st, j = 0; i <= ed; i++) {
        if (stops[j] == i) {
            add(x, i);
            j++;
        } else add(i, x);
    }
}

void solve() {
    cin >> n >> m;
    int l = m + n;
    e.assign(n + 1, {});
    in.assign(l + 1, {});
    dep.assign(l + 1, {});
    while (m--) {
        int k;
        cin >> k;
        vi stops(k);
        cin >> stops;
        add(stops);
    }
    std::queue<int> q;
    for (int i = 1; i <= l; i++) {
        if (!in[i]) q.push(i), dep[i] = (i <= n);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : e[u]) {
            if (!in[v]) continue;
            in[v]--;
            if (!in[v]) q.push(v), dep[v] = std::max(dep[v], dep[u] + (v <= n));
        }
    }
    int ans = 0;
    for (int i : dep) ans = std::max(ans, i);
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}