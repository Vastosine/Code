// Problem : D. Black, Gray and White https://codeforces.com/contest/2283/problem/D
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
int n;
vector<vi> e;
vi c;

void dfs(int u, int col = 0) {
    c[u] = col;
    int x = 0;
    for (int v : e[u]) {
        if (!~c[v]) {
            if (col) dfs(v, col);
            else {
                x++;
                dfs(v, x);
            }
        }
    }
}

auto Main([[maybe_unused]] int C = 0) {
    cin >> n;
    assign(n + 1, e);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    if (!(n & 1)) return n + 1;
    for (int u : {1, n / 2 + 1, n}) {
        c.assign(n + 1, -1);
        dfs(u);
        for (int l = 1, r = n; l < r; l++, r--) {
            if (u == l) l++;
            if (u == r) r--;
            if (c[l] != c[r]) {
                if (u == 1) return n + 2;
                if (u == n) return n;
                return n + 1;
            }
        }
    }
    return n + 1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
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