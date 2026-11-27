#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
ll popcnt(ll x) { return __builtin_popcountll(x); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n0";
        return 0;
    }
    vector<vi> nxt(n);
    vi in(n), pre(n, -1);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        int u = i, v;
        while (k--) {
            cin >> v;
            nxt[u].push_back(v);
            in[v]++;
            pre[v] = u;
        }
    }
    int st = 0;
    for (int i = 0; i < n; i++) if (!in[i]) st = i;
    vi o(1, st), dep(n);
    dep[st] = 1;
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : nxt[u]) {
            o.push_back(v);
            dep[v] = dep[u] + 1;
        }
    }
    int mx = *max_element(dep.begin(), dep.end());
    vector<vi> ans;
    for (int i = 0; i < n; i++) {
        if (mx == dep[i]) {
            ans.push_back({});
            int u = i;
            while (~u) {
                ans.back().push_back(u);
                u = pre[u];
            }
        }
    }
    for (auto &i : ans) reverse(i.begin(), i.end());
    Sort(ans);
    cout << ans[0].size() << "\n";
    for (int i = 0; i < ans[0].size(); i++) cout << ans[0][i] << " \n"[i == mx - 1];
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
