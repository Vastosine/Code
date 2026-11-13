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

int f(int x) {
    int ans = 0;
    while (x) {
        ans += (x % 10) * (x % 10);
        x /= 10;
    }
    return ans;
}

bool check(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}


auto Main([[maybe_unused]] int C = 0) {
    int l, r;
    cin >> l >> r;
    vector<vi> pre(1e5);
    for (int i = l; i <= r; i++) {
        pre[f(i)].push_back(i);
    }
    int cnt = 0;
    for (int x = l; x <= r; x++) {
        if (pre[x].empty()) {
            int ans = 0;
            vi vis(1e5);
            for (int y = x; y > 1; y = f(y)) {
                if (vis[y]) {
                    ans = 0;
                    break;
                }
                vis[y] = 1;
                ans++;
            }
            if (check(x)) ans *= 2;
            if (ans) cout << x << " " << ans << "\n", cnt++;
        }
    }
    if (!cnt) cout << "SAD";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
