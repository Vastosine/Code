// Problem : D. Silhouette https://codeforces.com/contest/2254/problem/D
// Time    : 2026-09-28 15:53:24
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

vi solve() {
    int n;
    cin >> n;
    struct Data {
        int x, i;
        bool operator<(const Data &data) const { return x < data.x; } 
    };
    vector<Data> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
        a[i].i = i;
    }
    sort(a);
    vi b(n);
    if (a[0].x) return {-1};
    for (int l = 0, r = 1, x = 0; l < n; l = r++) {
        while (r < n && a[r].x == a[l].x) r++;
        if (r == n) x++;
        else {
            int y = a[r].x - a[l].x;
            if (y % (r - l)) return {-1};
            int X = y / (r - l);
            if (X <= x) return {-1};
            x = X;
        }
        for (int i = l; i < r; i++) b[i] = x;
    }
    vi ans(n);
    for (int i = 0; i < n; i++) {
        ans[a[i].i] = b[i];
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