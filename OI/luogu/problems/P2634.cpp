// Problem : P2634 [国家集训队] 聪聪可可 https://www.luogu.com.cn/problem/P2634
// Time    : 2026-11-27 09:50:43
#include <algorithm>
#include <iostream>
#include <numeric>
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
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    szt n;
    cin >> n;
    vector<vector<pst>> e;
    vst vis, siz, fa, dis;
    assign(n + 1, e, vis, siz, fa, dis);
    auto isSon = [&] (szt u, szt v) { return !vis[v] && fa[u] != v; };
    auto getOrder = [&] (szt r) {
        vst o(1, r);
        fa[r] = r;
        for (szt i = 0; i < o.size(); i++) {
            szt u = o[i];
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v)) fa[v] = u, o.push_back(v);
            }
        }
        return o;
    };
    auto getCentroid = [&] (szt r) {
        vst o = getOrder(r);
        for (szt i : o) siz[i] = 1;
        for (szt i = o.size() - 1; i; i--) {
            szt u = o[i];
            siz[fa[u]] += siz[u];
        }
        auto check = [&] (szt u, szt n) {
            for (auto &[v, w] : e[u]) {
                if (isSon(u, v) && siz[v] > n / 2) return v;
            }
            return u;
        };
        szt u = r, v;
        while ((v = check(u, siz[r])) != u) u = v;
        return u;
    };
    auto calculate = [&] (szt r) {
        vst all(3), cur;
        all[0] = 1;
        szt ans = 1;
        for (auto &[s, d] : e[r]) {
            if (vis[s]) continue;
            cur.assign(3, 0);
            vst o(1, s);
            dis[s] = d;
            fa[s] = r;
            for (szt i = 0; i < o.size(); i++) {
                szt u = o[i];
                cur[dis[u] % 3]++;
                for (auto &[v, w] : e[u]) {
                    if (isSon(u, v)) dis[v] = dis[u] + w, o.push_back(v), fa[v] = u;
                }
            }
            // ans += cur[0];
            for (szt k = 0; k < 3; k++) {
                ans += all[k] * cur[(3 - k) % 3] * 2;
                all[k] += cur[k];
            }
        }
        return ans;
    };
    for (szt i = 1; i < n; i++) {
        szt u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    vst o(1, getCentroid(1));
    szt ans = 0, base = n * n;
    for (szt i = 0; i < o.size(); i++) {
        szt u = o[i];
        ans += calculate(u);
        vis[u] = 1;
        for (auto &[v, w] : e[u]) {
            if (!vis[v]) o.push_back(getCentroid(v));
        }
    }
    szt g = gcd(ans, base);
    ans /= g;
    base /= g;
    cout << ans << "/" << base;
    return ans;
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
