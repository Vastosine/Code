// Problem : B. Remainders Game https://codeforces.com/problemset/problem/687/B
// Time    : 2026-11-01 08:10:26
#include <iostream>
#include <map>
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

void init() {}

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    int K = k;
    map<int, int> ps;
    for (int p = 2; p * p <= K; p++) {
        while (K % p == 0) K /= p, ps[p]++;
    } 
    if (K > 1) ps[K]++;
    vi a(n);
    cin >> a;
    map<int, int> ap;
    for (autor i : a) {
        for (cautor [p, c] : ps) {
            int x = 0;
            if (p > i) break;
            while (i % p == 0 && c) i /= p, x++;
            ap[p] = max(ap[p], x);
        }
    }
    for (cautor [p, c] : ps) {
        if (c > ap[p]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"No", "Yes"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
