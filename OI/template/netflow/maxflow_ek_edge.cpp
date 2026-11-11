#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
const ll INF = 1ll << 60;

vector<vi> e;
vi to;
vll a;
int n;

ll EK(int s, int t) {
    if (s == t) return -1;
    ll ans = 0;
    while (true) {
        queue<int> q;
        vll add(n + 1);
        vi pre(n + 1, -1);
        q.push(s);
        add[s] = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) {
                ll w = add[t];
                while (u != s) {
                    int id = pre[u];
                    u = to[id ^ 1];
                    a[id] -= w;
                    a[id ^ 1] += w;
                }
                ans += w;
                break;
            }
            for (int i : e[u]) {
                int v = to[i];
                if (a[i] && !~pre[v]) {
                    add[v] = min(add[u], a[i]);
                    pre[v] = i;
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
    e.assign(n + 1, {});
    while (m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        e[u].push_back(to.size());
        to.push_back(v);
        a.push_back(w);
        e[v].push_back(to.size());
        to.push_back(u);
        a.push_back(0);
    }
    cout << EK(s, t);
}