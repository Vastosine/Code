#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    int n, m, T;
    cin >> n >> m >> T;
    struct CPU {
        int t, cur, end;
        CPU(int t) : t(t), cur(-1), end(-1) {}
    };
    vector<CPU> a;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    vector<vi> suit(n, vi(m));
    vi time(n);
    for (int i = 0; i < n; i++) {
        cin >> time[i];
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            suit[i][x - 1] = 1;
        }
    }
    vector<queue<int>> q(m);
    for (int i = 0; i < n; i++) {
        q[i % m].push(i);
    }
    vi ans(n, -inf);
    for (int t = 0, dx = 0, cnt = 0; cnt < n; t++) {
        for (int i = 0; i < m; i++) {
            if (t == a[i].end) {
                if (!time[a[i].cur]) ans[a[i].cur] += t, cnt++;
                else q[(i + dx) % m].push(a[i].cur);
            }
        }
        if (t && t % T == 0) dx++;
        for (int i = 0; i < m; i++) {
            if (int Q = (i + dx) % m; t >= a[i].end && !q[Q].empty()) {
                int x = q[Q].front();
                q[Q].pop();
                int scale = suit[x][i] ? 2 : 1;
                int y = min(a[i].t * scale, time[x]);
                time[x] -= y;
                a[i].end = t + y / scale + y % scale;
                a[i].cur = x;
                if (ans[x] == -inf) ans[x] = -t;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
