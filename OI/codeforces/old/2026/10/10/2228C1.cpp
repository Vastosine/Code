// Problem : C1. Cirno and Number (Easy Version) https://codeforces.com/problemset/problem/2228/C1
// Time    : 2026-10-10 12:01:36
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

vi int2vi(int x) {
    vi ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

int vi2int(const vi &a) {
    if (a.empty()) return 0;
    int ans = 0;
    for (int i = a.size() - 1ll; i >= 0; i--) ans = ans * 10 + a[i];
    return ans;
}
int C;

auto solve() {
    int X, n;
    cin >> X >> n;
    vi a(n);
    cin >> a;
    sort(a);
    if (!X) return a[0];
    vi x = int2vi(X);
    int k = x.size() - (vi2int(vi(x.size(), a[0])) > X);
    vi l(k, a[0]), L(k), r;
    for (int i = k - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            l[i] = a[j];
            L[i] = j;
            if (vi2int(l) <= X) break;
        }
    }
    if (!vi2int(l) && a[0]) return a[0] - X;
    int d = 1;
    for (int &i : L) {
        d = (i += d) / n;
        i %= n;
        r.push_back(a[i]);
    }
    if (d) r.push_back(a[0] ? a[0] : a[1]);
    int y = vi2int(l);
    int z = vi2int(r);
    // if (C > 10) return 0ll;
    return std::min(abs(X - y), abs(z - X));
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    C = c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    // const string Out[2] = {"No", "Yes"}; while (c--) cout << Out[solve()] << "\n";
    return 0;
}