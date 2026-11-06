// Problem : $name$ $url$
// Time    : $date$ $time$
#include <cstdio>
#include <cstdlib>
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

ll f[1000000][4];

auto Main([[maybe_unused]] int C = 0) {
    string s;
    cin >> s;
    int n = (int) s.length();
    f[0][0] = f[0][1] = 1;
    vi pre(26, -1);
    pre[s[0] - 'a'] = 0;
    for (int i = 1; i < n; i++) {
        f[i][0] = 1;
        int &p = pre[s[i] - 'a'], d = i - p;
        for (int j = 1; j < 4; j++) {
            f[i][j] += f[i - 1][j] + f[i - 1][j - 1];
            if (~p && (d = i - p) <= j) {
                f[i][j] -= p ? f[p - 1][j - d] : j - d == 0;
            }
        }
        p = i;
        // for (int j = 0; j < 4; j++) {
        //     cout << f[i][j] << " ";
        // }
        // cout << "\n";
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += f[n - 1][i];
    }
    return ans;
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */