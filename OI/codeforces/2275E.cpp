// Problem : E. Repentance Is Already on the Way https://codeforces.com/problemset/problem/2275/E
// Time    : 2026-11-06 09:53:18
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

int F(int x, int y) {
    return 1 + (x == y);
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n), b(n);
    cin >> a >> b;
    vector<vi> f(n, vi(2));
    int ans = F(a.back(), b.back());
    for (int i = 1; i < n; i++) {
        ans += F(b[i - 1], a[i]);
    }
    f.back() = {0, 0};
    for (int i = n - 2; ~i; i--) {
        f[i][0] = f[i + 1][0] + F(a[i], b[i + 1]);
        f[i][1] = max(f[i + 1][1], f[i + 1][0]) + F(a[i], b[i]);
    }
    return ans + max(f[0][0], f[0][1]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 1
 *  CHECK Vector Size                                : 1
 *  CHECK Multiple Test Clear                        : 1
 *  CHECK Restriction Value remain, border, negative : 1

 */