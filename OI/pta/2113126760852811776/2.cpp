// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <map>
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

auto Main([[maybe_unused]] int C = 0) {
    vi a(3);
    a[0] = C;
    cin >> a[1] >> a[2];
    if (a[0] & 1) {
        return -1;
    }
    queue<vi> q;
    map<vi, int> f;
    f[{a[0], 0, 0}] = 0;
    q.push({a[0], 0, 0});
    int t = a[0] / 2;

    auto has = [&] (int x, int y, int z) {
        return f.find({x, y, z}) != f.end();
    };
    while (!q.empty()) {
        if (has(t, t, 0)) return f[{t, t, 0}];
        if (has(0, t, t)) return f[{0, t, t}];
        if (has(t, 0, t)) return f[{t, 0, t}];
        const vi u = q.front();
        q.pop();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                int c = min(a[i] - u[i], u[j]);
                vi v = u;
                v[i] += c;
                v[j] -= c;
                if (f.find(v) == f.end()) {
                    q.push(v);
                    f[v] = f[u] + 1;
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    while (true) {
        cin >> C;
        if (!C) return 0;
        [[maybe_unused]] auto ans = Main(C);
        if (~ans) cout << ans << "\n";
        else cout << "NO\n";
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