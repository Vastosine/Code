// Problem : A. Enlarge GCD https://codeforces.com/problemset/problem/1034/A
// Time    : 2026-11-01 09:36:59
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

vi primes, spf;
int maxn = 1.51e7;
void init() {
    vector<bool> is(maxn, 1);
    spf.assign(maxn, 0);
    for (ll i = 2; i < maxn; i++) {
        if (is[i]) primes.push_back(i), spf[i] = i;
        for (int p : primes) {
            if (i * p >= maxn) break;
            is[i * p] = 0;
            spf[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    int G = 0;
    Sort(a);
    if (a.back() == a[0]) return -1;
    for (int i : a) G = gcd(G, i);
    for (int &i : a) i /= G;
    vi c(maxn);
    for (int x : a) {
        while (x > 1) {
            int p = spf[x];
            c[p]++;
            while (x % p == 0) x /= p;
        }
    }
    int ans = 0;
    for (int i : c) ans = max(ans, i);
    return n - ans;
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
