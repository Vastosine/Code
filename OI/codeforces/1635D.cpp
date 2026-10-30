// Problem : D. Infinite Set https://codeforces.com/problemset/problem/1635/D
// Time    : 2026-10-30 13:41:52
#include <iostream>
#include <set>
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

const int M = 1e9 + 7;

auto Main([[maybe_unused]] int C = 0) {
    int n, p;
    cin >> n >> p;
    vi a(n);
    cin >> a;
    Sort(a);
    set<int> s(a.begin(), a.end());
    vector<ll> f(p + 1);
    for (int i = 1, j = 0; i <= p; i++) {
        while (j < n && a[j] < (1ll << i)) {
            int x = a[j], k = 1;
            while (x) {
                if (x % 2) x = (x - 1) / 2;
                else if (x % 4 == 0) x /= 4;
                else break;
                if (s.find(x) != s.end()) {
                    k = 0;
                    break;
                }
            }
            f[i] += k;
            j++;
        }
        f[i] = ((f[i] + 2 * f[i - 1] - (i > 2 ? f[i - 3] : 0)) % M + M) % M;
    }
    return f[p];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
