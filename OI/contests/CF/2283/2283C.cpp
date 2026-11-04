// Problem : C. Big XOR https://codeforces.com/contest/2283/problem/C
// Time    : 2026-11-04 22:46:34
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    int k = 0, s = 0;
    while ((1 << k) <= n) k++;
    for (int i = 1; i <= n; i++) s ^= i;
    vi a(n + 1);
    while (k--) {
        if (!((1 << (k + 1)) & s)) {
            a[(1 << k)] = 1;
            s ^= (3 << k);
        }
    }
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
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