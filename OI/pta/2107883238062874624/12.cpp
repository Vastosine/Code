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

bool equal(double x, double y) {
    return abs(x - y) < 1e-6;
}

void print(int x, int g, string extra = " ") {
    if (g) cout << "-";
    cout << x << extra;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vi> a(m);
    vector<vector<double>> f(n, vector<double>(n));
    vi g(n, -1);
    auto read = [&] () {
        char c;
        int F = 0;
        cin >> c;
        int x = 0;
        if (c == '-') F = 1, cin >> c;
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = getchar();
        }
        g[x] = F;
        return x;
    };
    for (int i = 0; i < m; i++) {
        int t = 0;
        cin >> t;
        a[i].assign(t, 0);
        for (int j = 0; j < t; j++) {
            a[i][j] = read();
        }
        // double y = 1.0 / t;
        // for (int u : a[i]) {
        //     for (int v : a[i]) {
        //         if (g[u] == g[v]) continue;
        //         f[u][v] += y;
        //     }
        // }
    }
    // cin >> a;
    vi p(2);
    for (int i = 0; i < 2; i++) {
        p[i] = read();
    }
    // for (auto &i : f) {
    //     cout << i << "\n";
    // }
    for (int i = 0; i < m; i++) {
        double y = 1.0 / a[i].size();
        for (int u : a[i]) {
            if (u != p[0] && u != p[1]) continue;
            for (int v : a[i]) {
                if (g[u] == g[v]) continue; 
                f[u][v] += y;
            }
        }
    }
    vector<double> best(2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (f[p[i]][j] > best[i]) best[i] = f[p[i]][j];
        }
    }
    if (equal(best[0], f[p[0]][p[1]]) && equal(best[1], f[p[0]][p[1]])) {
        print(p[0], g[p[0]]);
        print(p[1], g[p[1]], "\n");
    } else {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                if (g[p[i]] + g[j] == 1 && equal(f[p[i]][j], best[i])) {
                    print(p[i], g[p[i]]);
                    print(j, g[j], "\n");
                }
            }
        }
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

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */