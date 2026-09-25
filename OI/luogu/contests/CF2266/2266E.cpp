// Problem : E. Prime Destruction https://codeforces.com/contest/2266/problem/E
// Time    : 2026-09-21 22:37:13

#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

vi vis;
vector<vi> ps;

vi getPrimes(int n) {
    vi p;
    vis.assign(n + 1, 1);
    ps.assign(n + 1, {});
    vis[0] = vis[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) continue;
        p.push_back(i);
        ps[i].push_back(i);
        for (int j = i * 2; j <= n; j += i) {
            vis[j] = false;
            ps[j].push_back(i);
        }
    }
    return p;
}

const vi primes = getPrimes(2e5);

int F(vi &f, int x, int k) {
    if (~f[x]) return f[x];
    if (x <= k) return f[x] = 0;
    if (vis[x]) return f[x] = 1;
    int ans = 0x7fffffffffffffff;
    for (int p : ps[x]) {
        // if (p > x || p * p > X) break;
        if (x % p == 0) {
            ans = std::min(ans, 1 + p * F(f, x / p, k));
        }
    }
    return f[x] = ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n), f(n + 1, -1);
    cin >> a;
    int ans = 0;
    for (int i : a) {
        if (vis[i] || i <= k) {
            ans += i > k;
            continue;
        }
        ans += F(f, i, k);
    }
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}