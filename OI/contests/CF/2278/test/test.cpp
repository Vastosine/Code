// Problem : $name$ $url$
// Time    : $date$ $time$
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

vi primes;
vector<bool> is;
void init() {
    int n = 1e7 + 1;
    is.assign(n, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i < n; i++) {
        if (is[i]) primes.push_back(i);
        for (cautor p : primes) {
            if (1ll * i * p >= n) break;
            is[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

const ll M = 1e9 + 7;
ll qpow(ll x, ll n) {
    return n ? qpow(x % M * x % M, n / 2) * (n & 1 ? x % M : 1) % M : 1;
}

auto Main([[maybe_unused]] int C = 0) {
    cout << primes << "\n";
    int x, n;
    cin >> x >> n;
    cout << qpow(x, n);
    return 0;
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
