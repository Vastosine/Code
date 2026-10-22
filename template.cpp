// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    return 0;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}