// Brute force template: PERMUTATIONS
//
// Use when the answer depends on the ORDER of the elements and n is tiny
// (n <= 8, 8! = 40320; n = 9 is already 362880 * work per permutation).
//
// Copy this file to ..\brute.cpp, then:
//   1. read the input in solve()
//   2. sort the array (next_permutation needs sorted start to walk all perms)
//   3. put the evaluation of ONE ordering where marked EDIT
//
// Run:  .\stress.ps1 -Sol ..\..\OI\codeforces\abc.cpp -N 300
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
    Sort(a);                       // required: enumerate from the sorted start

    ll ans = NEG;
    do {
        // ---- EDIT: score this permutation -------------------------------
        ll cur = 0;
        for (int i = 0; i < n; i++) cur += (ll) a[i] * (i + 1);   // example
        ans = max(ans, cur);
        // -----------------------------------------------------------------
    } while (next_permutation(a.begin(), a.end()));

    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}
