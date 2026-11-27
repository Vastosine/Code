// Problem : B. Kay and Snowflake https://codeforces.com/problemset/problem/685/B
// Time    : 2026-11-27 08:24:33
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    szt n, q;
    cin >> n >> q;
    vst fa(n + 1);
    vector<vst> s(n + 1);
    for (szt i = 2; i <= n; i++) cin >> fa[i], s[fa[i]].push_back(i);
    vst o(1, 1), siz(n + 1), g(n + 1);
    for (szt i = 0; i < n; i++) {
        szt u = o[i];
        for (szt v : s[u]) o.push_back(v);
    }
    for (szt i = n - 1; ~i; i--) {
        szt u = o[i];
        siz[u]++;
        siz[fa[u]] += siz[u];
    }
    auto find = [&] (auto &&f, szt u, szt n) -> szt {
        for (szt v : s[u]) {
            if (siz[v] > n / 2) return f(f, v, n);
        }
        return u;
    };
    while (q--) {
        szt x;
        cin >> x;
        cout << find(find, x, siz[x]) << "\n";
    }
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
