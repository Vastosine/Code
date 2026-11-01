// Problem : A. Enlarge GCD https://codeforces.com/problemset/problem/1034/A
// Time    : 2026-11-01 08:52:04
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

vi primes;
void init() {
    vector<bool> is;
    int n = 1.51e7;
    is.assign(n, 1);
    for (int i = 2; i < n; i++) {
        if (is[i]) primes.push_back(i);
        for (ll p : primes) {
            if (i * p >= n) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
    // cout << primes.size() << "\n";
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    Sort(a);
    if (a.back() == a[0]) return -1;
    map<int, int> c;
    vector<unordered_map<int, int>> ps(n);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        for (int p : primes) {
            if (p * p > x) break;
            if (x % p == 0) c[p]++;
            while (x % p == 0) x /= p, ps[i][p]++;
        }
        if (x > 1) c[x]++, ps[i][x]++;
    }
    int ans = n;
    for (auto &[p, x] : c) {
        if (x == n) {
            int mn = 100, res = 0;
            for (int i = 0; i < n; i++) {
                int y = ps[i][p];
                if (y < mn) mn = y, res = 0;
                if (y == mn) res++;
            }
            ans = min(res, ans);
        } else ans = min(ans, (n - x));
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
