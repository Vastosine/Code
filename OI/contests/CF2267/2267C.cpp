// Problem : C. GCD Treasury https://codeforces.com/contest/2267/problem/C
// Time    : 2026-09-25 22:57:24
#include <iostream>
#include <numeric>
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
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

using std::gcd;

vi primes, isp;

void init(int n) {
    isp.assign(n + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) continue;
        primes.push_back(i);
        for (int j = i * 2; j <= n; j += i) {
            isp[j] = false;
        }
    }
}

void solve() {
    int n, x;
    cin >> n >> x;
    vi a(n);
    cin >> a;
    vi ps;
    if (isp[x]) ps.push_back(x);
    else {
        for (int p : primes) {
            if (x % p == 0) ps.push_back(p);
            while (x % p == 0) x /= p;
            if (p > x) break;
        }
    }
    int ans = 0;
    for (int p : ps) {
        int tmp = 0;
        for (int i : a) {
            if (gcd(i, p) > 1) tmp += i;
        }
        ans = std::max(ans, tmp);
    }
    cout << ans << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    init(3e5);
    while (c--) solve();
    return 0;
}