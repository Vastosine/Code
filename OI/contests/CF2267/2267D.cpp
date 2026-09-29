// Problem : D. Backrooms Hill https://codeforces.com/contest/2267/problem/D
// Time    : 2026-09-25 22:57:25
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

bool solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    if (n <= 2) return true;
    vi b[2];
    for (int i = 0; i < n; i++) {
        b[i % 2].push_back(a[i]);
    }
    auto cmp = [] (int x, int y) { return x > y; };
    sort(b[0], cmp);
    sort(b[1], cmp);
    int k = b[0][0] < b[1][0], s = 0, i[2] = {};
    i[k]++;
    for (int _ = 1; _ < n; _++) {
        if (i[k] >= b[k].size() || (i[!k] < b[!k].size() && b[k][i[k]] < b[!k][i[!k]])) {
            s++;
            if (s > 2) return false;
            i[!k]++;
        } else {
            s--;
            if (s < 0) return false;
            i[k]++;
        }
    }
    return true;
}

#undef int

const string OUT[2] = {"NO", "YES"};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << OUT[solve()] << "\n";
    return 0;
}