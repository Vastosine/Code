// Brute force template: SUBSETS / SUBMASKS
//
// Use when you must decide WHICH elements to take (2^n masks).
// n <= 20 is the practical limit for 2^n, and 2^n * n ~ 2e7 for n = 20.
//
// Two patterns are below:
//   (A) enumerate every subset                 -> "pick any set"
//   (B) enumerate every submask of every mask  -> "split a set into two parts"
//                                             -> "pick a group inside a group"
//
// Copy this file to ..\brute.cpp and edit the marked places.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }

auto solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;

    // ---------------- (A) every subset -------------------------------
    ll ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll cost = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                // ---- EDIT: cost of taking element i --------------------
                cost += a[i];
                cnt++;
            }
        }
        // ---- EDIT: accept / reject this subset -------------------------
        if (cost <= 100) ans = max(ans, (ll) cnt);
    }
    // -----------------------------------------------------------------

    // ---------------- (B) every submask of every mask ----------------
    // for (int mask = 0; mask < (1 << n); mask++) {
    //     for (int sub = mask; ; sub = (sub - 1) & mask) {
    //         int rest = mask ^ sub;          // the other group
    //         // EDIT: score the split (mask -> sub + rest)
    //         if (sub == 0) break;            // (sub - 1) & mask on 0 loops forever
    //     }
    // }
    // -----------------------------------------------------------------

    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}
