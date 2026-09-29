// Problem : E. Chronostasis https://codeforces.com/contest/2254/problem/E
// Time    : 2026-09-28 16:22:05
#include <iostream>
#include <set>
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

vi solve() {
    int n;
    cin >> n;
    vi a;
    std::multiset<int> b;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0) a.push_back(x);
        else b.insert(-x);
        sum += x;
    }
    if (sum <= 0) return {-1};
    sort(a);
    vi ans;
    for (int i = 0, x = 0, p = 0; i < n; i++) {
        auto it = b.lower_bound(x);
        if (it == b.cbegin()) ans.push_back(x += a[p++]);
        else ans.push_back(x -= *--it), b.erase(it);
    }
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