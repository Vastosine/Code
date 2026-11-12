// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

const int N = 1e6;

auto Main([[maybe_unused]] int C = 0) {
    int n, st;
    struct Node {
        int nxt, val, id;
    };
    cin >> st >> n;
    vector<Node> a(N + 1);
    for (int i = 0; i < n; i++) {
        int add;
        cin >> add;
        cin >> a[add].val >> a[add].nxt;
    }
    vi f(n + 2);
    for (int i = 1, u = st; i <= n; i++, u = a[u].nxt) {
        if (u < 0 || u >= N) {
            n = i - 1;
            break;
        }
        a[u].id = i;
        f[i] = u;
    }
    for (int i = 1; i <= n; i++) {
        int u = f[i];
        a[u].nxt = f[n + (i > n / 2) - i];
    }
    for (int i = 1, u = f[n]; i <= n; i++, u = a[u].nxt) {
        if (i == n) printf("%05d %d -1\n", u, a[u].val);
        else printf("%05d %d %05d\n", u, a[u].val, a[u].nxt);
    }
    return 0;
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
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
