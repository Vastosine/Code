// Problem : C. MEXOR https://codeforces.com/contest/2245/problem/C
// Time    : 2026-09-30 09:57:49
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

bool check(const vi &a, int k) {
    int n = a.size();
    vi vis(n + 1);
    int l = 0, ans = 0;
    for (int i : a) {
        vis[i] = true;
        while (vis[l]) l++;
        ans ^= l;
    }
    return ans == k;
}

auto solve() {
    int n, k;
    cin >> n >> k;
    int x = k ^ n;
    if (k == 0 || x >= n) {
        x = n ^ (n - 1) ^ k;
        if (x >= n - 1) return cout << "NO\n", void();
        cout << "YES\n";
        for (int i = n - 2; i + 1; i--) if (i != x) cout << i << " ";
        cout << x << " " << n - 1 << "\n";
        return;
    }
    if (x >= n) {
        cout << "NO\n";
        return ;
    }
    if (x == 0) {
        cout << "YES\n";
        for (int i = n - 1; i + 1; i--) cout << i << " ";
        cout << "\n";
        return;
    }
    vi ans;
    for (int i = 1; i < n; i++) {
        if (i == x) continue;
        ans.push_back(i);
    }
    ans.push_back(0);
    ans.push_back(x);
    cout << "YES\n" << ans << "\n";
    // if (!check(ans, k)) std::cerr << n << " " << k << "\n";
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}