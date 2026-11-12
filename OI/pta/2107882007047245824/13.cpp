// Problem : $name$ $url$
// Time    : $date$ $time$
#include <iostream>
#include <map>
#include <string>
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

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n), v, dep, fa;
    map<int, int> f;
    vector<pii> t;
    cin >> a;
    for (int x : a) {
        if (t.empty()) {
            v.push_back(x);
            t.push_back({});
            dep.push_back(0);
            fa.push_back(-1);
        } else {
            int u = 0;
            while (true) {
                auto &[l, r] = t[u];
                int &p = x < v[u] ? l : r;
                if (p) {
                    u = p;
                } else {
                    p = v.size();
                    v.push_back(x);
                    t.push_back({});
                    dep.push_back(dep[u] + 1);
                    fa.push_back(u);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        f[v[i]] = i;
    }
    int q;
    cin >> q;
    const string format[] = {
        "%d and %d are siblings",
        "%d and %d are on the same level",
        "%d is the parent of %d",
        "%d is the left child of %d",
        "%d is the right child of %d",
    };
    auto F = [&] () {
        string s;
        while (s.empty()) getline(cin, s);
        if (s.back() == 't') {
            int x;
            sscanf(s.c_str(), "%d is the root", &x);
            return x == v[0];
        }
        for (int op = 0; op < 5; op++) {
            int x, y;
            int k = sscanf(s.c_str(), format[op].c_str(), &x, &y);
            if (k != 2 || (op < 2 && s.back() != format[op].back())) continue;
            if (f.find(x) == f.end() || f.find(y) == f.end()) return false;
            x = f[x];
            y = f[y];
            switch (op) {
                case 0: return fa[x] == fa[y];
                case 1: return dep[x] == dep[y];
                case 2: return fa[y] == x;
                case 3: return t[y].first == x;
                case 4: return t[y].second == x;
            }
        }
        return false;
    };
    const string OUT[2] = {"No", "Yes"};
    while (q--) {
        cout << OUT[F()] << "\n";
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
