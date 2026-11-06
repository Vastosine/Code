// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <locale>
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
    vi a(n);
    cin >> a;
    int T = *max_element(a.begin(), a.end());
    vector<vi> f(n);
    for (int i = 0, t = 1, c = 0; i < T * 10; i++) {
        for (int j = 0; j < n; j++) {
            if ((int) f[j].size() < 10 * a[j]) {
                f[j].push_back(t);
                t++;
                if (c == n - 1) t++;
                if ((int) f[j].size() == 10 * a[j]) c++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "#" << i + 1 << "\n";
        for (int j = 1; j <= 10 * a[i]; j++) {
            cout << f[i][j - 1] << " \n"[j % 10 == 0];
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
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