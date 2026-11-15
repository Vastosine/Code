// Problem : C. Reverse and Double https://codeforces.com/contest/2280/problem/C
// Time    : 2026-11-15 10:10:36
#include <iostream>
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
    int n;
    cin >> n;
    vi a(n), b(n);
    cin >> a;
    // b[0] is 0;
    for (int i = 1; i < n; i++) b[i] = abs(a[i] - a[i - 1]);
    int st = max_element(b.begin(), b.end()) - b.begin();
    if (!b[st]) return st;
    if (a[st] > a[st - 1]) {
        for (int i = 0; i * 2 < n; i++) {
            swap(a[i], a[n - i - 1]);
        }
        for (int i = 1; i < n; i++) b[i] = abs(a[i] - a[i - 1]);
        st = max_element(b.begin(), b.end()) - b.begin();
    } 
    int pre = *max_element(b.begin(), b.begin() + st), ans = b[st];
    vi q(n);
    // q.back() = b.back();
    for (int i = n - 1; i; i--) q[i - 1] = max(b[i], q[i]);
    for (int r = st, y = 0; r < n && y * 2 <= ans; r++, y = max(y, b[r])) {
        int cur = max({y * 2, pre, abs(a[st - 1] - a[r] * 2)});
        if (r < n - 1) cur = max({abs(a[st] * 2 - a[r + 1]), cur, q[r + 1]});
        ans = min(ans, cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
