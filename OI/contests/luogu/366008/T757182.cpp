// Problem : T757182 [ICPC 2019 Nanchang R] Eating Plan https://www.luogu.com.cn/problem/T757182?contestId=366008
// Time    : 2026-10-29 13:00:10
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

const ll M = 998857459;
vector<ll> P;

void init() {
    int n = 1e5 + 1;
    P.assign(n, 0);
    P[0] = 1;
    multiset<ll> s;
    for (int i = 1; i < n; i++) {
        P[i] = P[i - 1] * i % M;
        if (!P[i]) break;
    }
}

void Max(ll &x, ll y) {
    x = max(x, y);
}

auto Main(int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), can;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = (a[i - 1] + P[x]) % M;
        if (P[x]) can.push_back(i); 
    }
    vector<ll> f(n + 1);
    for (int l : can) {
        for (int r : can) {
            if (r < l) continue;
            Max(f[r - l + 1], (a[r] - a[l - 1] + M) % M);
        }
    }
    for (int i = 2; i <= n; i++) {
        Max(f[i], f[i - 1]);
    }
    while (m--) {
        ll x;
        cin >> x;
        int y = lower_bound(f.begin(), f.end(), x) - f.begin();
        if (y > n) cout << "-1\n";
        else cout << y << "\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
