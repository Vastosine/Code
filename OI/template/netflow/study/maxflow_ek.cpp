#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
const ll INF = 1ll << 60;

vector<vll> a;
int n;

ll EK(int s, int t) {
    if (s == t) return -1;
    ll ans = 0;
    while (true) {
        queue<int> q;
        vll add(n + 1);
        vi pre(n + 1);
        q.push(s);
        add[s] = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) {
                while (u != s) {
                    int v = u;
                    u = pre[u];
                    a[u][v] -= add[t];
                    a[v][u] += add[t];
                }
                ans += add[t];
                break;
            }
            for (int v = 1; v <= n; v++) {
                if (a[u][v] && !pre[v]) {
                    add[v] = min(add[u], a[u][v]);
                    pre[v] = u;
                    q.push(v);
                }
            }
        }
        if (!add[t]) return ans;
    } 
}

int main() {
    int m, s, t;
    cin >> n >> m >> s >> t;
    a.assign(n + 1, vll(n + 1));
    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        a[u][v] += w;
    }
    cout << EK(s, t);
}