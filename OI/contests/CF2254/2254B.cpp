// Problem : B. Evanescent https://codeforces.com/contest/2254/problem/B
// Time    : 2026-09-28 11:09:57
#include <iostream>
#include <vector>
#include <algorithm>
// #define int long long
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

int solve() {
    int n;
    string s;
    cin >> n >> s;
    int k = 0;
    for (int i = 1; i < n - 1; i++) {
        if (s[i - 1] == s[i + 1] && s[i] != s[i - 1]) {
            s[i] = s[i - 1];
            k = 1;
            break;
        }
    }
    for (int i = 1; !k && i < n - 1; i++) {
        if (s[i] != s[i - 1] && s[i] != s[i + 1]) {
            s[i] = s[i - 1];
            break;
        }
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) ans++;
    }
    return ans;
    return 0;
}

#undef int

const string OUT[2] = {"NO", "YES"};
const string Out[2] = {"No", "Yes"};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // while (c--) cout << OUT[solve()] << "\n";
    // while (c--) cout << Out[solve()] << "\n";
    return 0;
}