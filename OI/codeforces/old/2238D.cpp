// Problem : D. Storming Arasaka https://codeforces.com/problemset/problem/2238/D
// Time    : 2026-10-10 11:01:36
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
template<typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }
int abs(int x) { return x < 0 ? -x : x; }

vi getPrimes(int n) {
    vi vis(n + 1), ans;
    for (int i = 2; i * i <= n; i++) {
        if (vis[i]) continue;
        for (int j = i * 2; j <= n; j += i) {
            vis[j] = true;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) ans.push_back(i);
    }
    return ans;
}

vi primes = getPrimes(2e6);

auto solve() {
    int n;
    cin >> n;
    int N = n;
    int ans = -1;
    for (int p : primes) {
        if (p > n || p * p > N) break;
        if (n % p == 0) ans++;
        while (n % p == 0) ans++, n /= p;
    }
    if (n > 1) ans += 2;
    return ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}