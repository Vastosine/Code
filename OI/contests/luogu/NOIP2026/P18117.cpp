// Problem : P18117 [NOIP2026] 青鸟 / bird（民间数据） https://www.luogu.com.cn/problem/P18117?contestId=376524
// Time    : 2026-11-28 17:20:36
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? " " : "") << a[i]; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<vector<T>> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? "\n" : "") << a[i]; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename T> void Unique(vector<T> &a) { sort(a.begin(), a.end()), a.erase(unique(a.begin(), a.end()), a.end()); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

const szt M = 1e9 + 7;

ll qpow(ll x, ll n, szt m = M) {
    x = (x % m + m) % m;
    ll res = 1;
    while (n) {
        if (n & 1) (res *= x) %= m;
        x = x * x % m;
        n >>= 1;
    }
    return res % m;
}

int __c;
szt n, p;
vst a;

szt brute() {
    auto hash = [&] (const vst &a) {
        szt res = 0;
        for (auto &i : a) res = res * (n + 1) + i;
        return res;
    };
    vb vis(qpow(n + 1, n));
    vector<vst> o(1, a);
    vis[hash(a)] = 1;
    ll ans = 0;
    for (szt i = 0; i < o.size(); i++) {
        vst u = o[i];
        szt s = 0;
        for (auto &i : u) s += i;
        ans = (ans + qpow(p, s)) % M;
        for (szt x = 0; x < n; x++) {
            for (szt l = 0; l <= x; l++) {
                for (szt r = x; r < n; r++) {
                    vst v = u;
                    for (szt j = l; j <= r; j++) {
                        v[j] = x + 1;
                    }
                    if (szt h = hash(v); !vis[h]){
                        vis[h] = 1;
                        o.push_back(v);
                    }
                }
            }
        }
    }
    return ans;
}

szt Main(int = 0) {
    cin >> n >> p;
    a.assign(n, 0);
    cin >> a;
    if (__c < 3) return brute();
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> __c;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
