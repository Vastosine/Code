// Problem : D. The 67th OEIS Problem https://codeforces.com/problemset/problem/2218/D
// Time    : 2026-10-24 09:50:49
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

vi getPrimes(int n) {
    vi is(n + 1, 1);
    for (int i = 2; i * i <= n; i++) {
        if (is[i]) {
            for (int j = i * 2; j <= n; j += i) {
                is[j] = 0;
            }
        }
    }
    vi ans;
    for (int i = 2; i <= n; i++) if (is[i]) ans.push_back(i);
    return ans;
}

vi primes = getPrimes(1e6);
vector<ll> ans;

auto solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
    cout << "\n";
}

bool check(int n) {
    set<ll> s;
    for (int i = 1; i < n; i++) {
        ll g = gcd(ans[i], ans[i - 1]);
        if (s.find(g) == s.end()) s.insert(g);
        else return cerr << i << " ", false;
    }
    return true;
}

// 4, 8, ..., 2^n, 2^n, 2 * 3, 2 * 3^2, ..., 2 * 3^m, 3 * 5, ...
void init(int n) {
    ll q = 2;
    ll maxx = (ll) 1e18;
    set<ll> s;
    ans.push_back(1);
    for (int t = 2; t < (int) INF; t++) {
        for (ll x = q * t, tr = 0; x < maxx / t && tr < 3; x *= t, tr++) {
            ll g = gcd(x, ans.back());
            if (s.find(g) != s.end()) continue;
            ans.push_back(x);
            s.insert(g);
            if ((int) ans.size() > n) return;
            q = t;
            tr--;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    init(10005);
    // while (c--) cout << solve() << "\n";
    cerr << check(10000) << "\n";
    while (c--) solve();
    // cerr << clock() / 1000.0;
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}