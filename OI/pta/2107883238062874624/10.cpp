// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <stack>
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
    vi dep(n + 1), fa(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> fa[i];
        if (fa[i] == -1) dep[i] = 1;
    }
    int dm = 1;
    for (int u = 1; u <= n; u++) {
        if (dep[u]) continue;
        stack<int> s;
        int v = u;
        while (!dep[v]) {
            s.push(v);
            v = fa[v];
        }
        while (!s.empty()) {
            int x = s.top();
            s.pop();
            dep[x] = dep[fa[x]] + 1;
            dm = max(dm, dep[x]);
        }
    }
    cout << dm;
    for (int i = 1, t = 0; i <= n; i++) {
        if (dep[i] == dm) cout << " \n"[!t] << i, t++;
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