// Problem : E. Partition of a Binary String https://codeforces.com/contest/2283/problem/E
// Time    : 2026-11-04 22:46:34
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

const int M = 998244353;
vector<ll> f, g;
void init() {
    int n = 5005;
    vector<vector<ll>> tmp(2, vector<ll>(n + 1)); // after submiting
    assign(n + 1, f, g);
    g[0] = g[2] = g[3] = 1;
    for (int i = 4; i <= n; i++) g[i] = (g[i - 2] + g[i - 3]) % M;
    f[0] = f[1] = tmp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            (f[i] += tmp[i % 2][j] = (tmp[(i - 1) % 2][j] * j + tmp[(i - 1) % 2][j - 1]) % M) %= M;
        }
    }
    // cout << g << "\n" << f << "\n";
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    string s;
    cin >> n >> s;
    ll ans = n, num = 0;
    vi v(n);
    vi c(2);
    for (int i = 0; i < n; i++) {
        v[i] = (i && s[i] != s[i - 1]) || (i < n - 1 && s[i] != s[i + 1]);
        ans += v[i];
        if (!v[i]) c[s[i] - '0']++;
    }
    num = (f[c[0]] * f[c[1]]) % M;
    for (int l = 0; l < n - 1; ) {
        while (!v[l]) l++;
        int r = l;
        while (r < n - 1 && s[r] != s[r + 1]) r++;
        if (l >= n - 1) break;
        (num *= g[r - l + 1]) %= M;
        l = r + 1;
    }
    cout << ans << " " << num << "\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
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

 */