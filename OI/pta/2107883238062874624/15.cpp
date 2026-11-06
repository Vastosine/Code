// Problem : $name$ $url$
// Time    : $date$ $time$
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
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

ll D(const vector<vi> &a) {
    return 1ll * a[0][0] * a[1][1] - 1ll * a[0][1] * a[1][0];
}

ll S(pii x, pii y, pii z) {
    return abs(D({
        { y.first - x.first, y.second - x.second},
        { z.first - x.first, z.second - x.second}
    }));
}

double an(pii x) {
    return atan(x.second * 1.0 / x.first);
}

double an(pii x, pii y) {
    return abs(an(y) - an(x));
}

pii operator-(const pii &p, const pii &q) {
    return {p.first - q.first, p.second - q.second};
}

double len(pii x) {
    return sqrt(1.0 * x.first * x.first + 1.0 * x.second * x.second);
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vector<pii> a(n);
    for (auto &[u, v] : a) cin >> u >> v;
    ll ans = S(a[0], a[1], a[2]);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) return 0.0;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = i + 1; j < n; j++) {
    //         for (int k = j + 1; k < n; k++) {
    //             ans = min(ans, S(a[i], a[j], a[k]));
    //         }
    //     }
    // }
    // const double T = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<double, int>> b;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                b.push_back({an(a[j] - a[i]), j});
            }
        }
        Sort(b);
        for (int j = 1; j < n; j++) {
            ans = min(ans, S(a[i], a[b[j - 1].second], a[b[j % (n - 1)].second]));
        }
        // Sort(b, [&] (pii x, pii y) {
        //     return an(x - a[i]) < an(y - a[i]);
        // });
        // for (int j = 0; j < n; j++) {
        //     if (a[i] == b[j]) continue;
        //     for (int k = j + 1; k != j; k = (k + 1) % n) {
        //         if (a[i] == b[k]) continue;
        //         auto tmp = an(b[j] - a[i], b[k] - a[i]);
        //         if (tmp > asin(T)) break;
        //         ans = min(ans, S(a[i], b[j], b[k]));
        //     }
        //     for (int k = j - 1; k != j; k = (k + n - 1) % n) {
        //         if (a[i] == b[k]) continue;
        //         if (an(b[j] - a[i], b[k] - a[i]) > asin(T)) break;
        //         ans = min(ans, S(a[i], b[j], b[k]));
        //     }
        // }
    }
    // for (int i = 0; i < n; i++) {
    //     auto b = a;
    //     Sort(b, [&] (pii x, pii y) {
    //         return len(x - a[i]) < len(y - a[i]);
    //     });
    //     for (int j = 0; j < n; j++) {
    //         if (a[i] == b[j]) continue;
    //         for (int k = j + 1; k != j; k = (k + 1) % n) {
    //             if (a[i] == b[k]) continue;
    //             if (len(b[j] - a[i]) * len(b[k] - a[i]) > ans / T) break;
    //             ans = min(ans, S(a[i], b[j], b[k]));
    //         }
    //     }
    // }
    return ans / 2.0;
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << fixed << setprecision(3) << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

// HACKED
// 6
// 5 5
// 0 0
// 1 0
// -5 2
// 0 1
// 2 -5

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */