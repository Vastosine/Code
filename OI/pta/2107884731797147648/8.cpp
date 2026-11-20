#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
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
    vector<vi> a(4, vi(4));
    vi vis(10);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) cin >> a[i][j], vis[a[i][j]] = 1;
    }
    int y = 0;
    for (int i = 1; i <= 9; i++) if (!vis[i]) y = i;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) if (!a[i][j]) a[i][j] = y; 
    }
    for (int i = 0; i < 3; i++) {
        int x, y;
        cin >> x >> y;
        cout << a[x][y] << "\n";
        
    }
    int t;
    cin >> t;
    int s = 0;
    if (t < 4) {
        for (int i = 1; i <= 3; i++) s += a[t][i];
    } else if (t < 7) {
        for (int i = 1; i <= 3; i++) s += a[i][t - 3];
    } else if (t == 7) s = a[1][1] + a[2][2] + a[3][3];
    else s = a[1][3] + a[2][2] + a[3][1];
    int p[] = {10000, 36, 720, 360, 80, 252, 108, 72, 54, 180, 72, 180, 119, 36, 306, 1080, 144, 1800, 3600};
    return p[s - 6];
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
