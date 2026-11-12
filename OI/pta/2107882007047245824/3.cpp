// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iomanip>
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

int f(int h, int m) {
    return m + 60 * h;
}

auto Main([[maybe_unused]] int C = 0) {
    const int N = 1000;
    int n;
    cin >> n;
    for (int d = 0; d < n; d++) {   
        int s = 0, c = 0;
        vi a(N + 1, -1);
        while (true) {
            int id;
            char op;
            int h, m;
            scanf("%d %c %d:%d", &id, &op, &h, &m);
            int t = f(h, m);
            if (!id) {
                break;
            }
            if (op == 'S') {
                a[id] = t;
            } else {
                if (~a[id]) {
                    s += t - a[id];
                    c++;
                    a[id] = -1;
                }
            }
        }
        int ave = c ? s / c : 0, remain = s - ave * c;
        if (remain && remain >= c / 2) ave++;
        cout << c << " " << ave << "\n";
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
