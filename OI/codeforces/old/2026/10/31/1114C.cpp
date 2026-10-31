// Problem : C. Trailing Loves (or L'oeufs?) https://codeforces.com/problemset/problem/1114/C
// Time    : 2026-10-31 16:42:02
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#define car const auto &
#define ar auto &
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

// vi is, primes;
void init() {
    // int n = 1e6 + 1;
    // is.assign(n, 1);
    // is[0] = is[1] = 0;
    // for (int i = 2; i < n; i++) {
    //     if (is[i]) primes.push_back(i);
    //     for (const auto &p : primes) {
    //         if (1ll * p * i >= n) break;
    //         is[i * p] = 0;
    //         if (i % p == 0) break;
    //     }
    // }
}

auto Main([[maybe_unused]] int C = 0) {
    ll n, b;
    cin >> n >> b;
    map<ll, ll> ps;
    for (ll p = 2; p * p <= b; p++) {\
        while (b % p == 0) b /= p, ps[p]++;
    }
    if (b > 1) ps[b]++;
    ll ans = INF;
    for (car [p, c] : ps) {
        ll m = n, res = 0;
        while (m /= p) {
            res += m;
        }
        ans = min(ans, res / c);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
