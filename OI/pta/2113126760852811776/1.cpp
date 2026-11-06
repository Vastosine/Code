// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <queue>
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

auto Main([[maybe_unused]] int &C) {
    int n, st, ed;
    cin >> n;
    if (n == 0) {
        C = -1;
        return 0;
    }
    cin >> st >> ed;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    queue<int> q;
    q.push(st);
    vi f(n + 1, -1);
    f[st] = 0;
    while (!q.empty() && !~f[ed]) {
        int u = q.front();
        q.pop();
        for (int j = -1; j < 2; j += 2) {
            int v = u + j * a[u];
            if (v < 1 || v > n) continue;
            if (!~f[v]) {
                f[v] = f[u] + 1;
                q.push(v);
            }
        }
    }
    return f[ed];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; ) {
        [[maybe_unused]] auto ans = Main(c);
        if (!~c) return 0;
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