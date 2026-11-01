// Problem : G. Short Task https://codeforces.com/problemset/problem/1512/G
// Time    : 2026-11-01 07:44:58
#include <iostream>
#include <vector>
#include <algorithm>
#define cautor const auto &
#define autor auto &
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

vi primes, low, sigma, f;

void init() {
    int n = 1e7 + 1;
    assign(n, low, sigma, f);
    for (int i = 2; i < n; i++) {
        if (!low[i]) {
            primes.push_back(i); 
            low[i] = i;
        } 
        for (cautor p : primes) {
            if (1ll * i * p >= n) break;
            if (i % p) {
                low[i * p] = p;
            } else {
                low[i * p] = low[i] * p;
                break;
            }
        }
        // cout << low[i] << "\n";
    }
    sigma[1] = 1;
    for (cautor p : primes) {
        for (ll x = 1; x * p < n; x *= p) {
            sigma[x * p] = sigma[x] * p + 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!sigma[i]) {
            sigma[i] = sigma[i / low[i]] * sigma[low[i]];
        }
        if (sigma[i] < n && !f[sigma[i]]) f[sigma[i]] = i;
        // cout << sigma[i] << "\n";
    }

}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    return f[n] ? f[n] : -1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
