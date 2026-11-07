// Problem : D. Flip the Bit (Hard Version) https://codeforces.com/problemset/problem/2217/D
// Time    : 2026-11-07 18:37:08
// DIFF vs B: k = 1 -> k >= 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
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
    int n, k;
    cin >> n >> k;
    vi a(n), b(n);
    cin >> a;
    int tr;
    while (k--) {
        int x;
        cin >> x;
        b[x - 1] = 1;
        tr = a[x - 1];
    }
    vi c, d;
    for (int l = 0, r = 0; l < n; l = r = r + 1) {
        int t = b[l];
        while (r < n - 1 && a[r + 1] == a[r]) {
            r++;
            t |= b[r];
        }
        c.push_back(a[l]);
        d.push_back(t);
    }
    int ans = 0, m = (int) d.size();
    vi vis(m);
    for (int i = 0; i < m; i++) {
        if (c[i] == tr) continue;
        if (!i) {
            if (d[1]) vis[1] = 1;
            else ans += 2;
        } else if (i == n - 1) {
            if (d[i - 1]) vis[i - 1] = 1;
            else ans += 2;
        } else if (!vis[i - 1] && !vis[i + 1]) {
            if (d[i + 1]) vis[i + 1] = 1;
            else ans += 2;
        }
    }
    for (int i = 0, t = 0; i < m; i++) {
        if (vis[i]) {
            ans += 1 + !t;
            t++;
        } else t = 0;
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

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 
 *  CHECK Output Format                              : 

 */