// Problem : $name$ $url$
// Time    : $date$ $time$
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
int n, m;
vector<vi> e;

bool check(const vi &vis) {
    for (int u = 1; u <= n; u++) {
        if (vis[u]) continue;
        for (int v : e[u]) {
            if (!vis[v]) return false;
        }
    }
    return true;
}
const string OUT[2] = {"NO", "YES"};

auto Main([[maybe_unused]] int C = 0) {
    cin >> n >> m;
    assign(n + 1, e);
    while (m--) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int K;
    cin >> K;
    while (K--) {
        int p;
        cin >> p;
        vi vis(n + 1);
        while (p--) {
            int x;
            cin >> x;
            vis[x] = 1;
        }
        cout << OUT[check(vis)] << "\n";
    }
    return 0; 
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ; init(); int C = 1;
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