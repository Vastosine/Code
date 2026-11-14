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

map<string, int> mp;

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    struct P {
        string name, fn;
        int g, has_an = 0;

        void input(int id) {
            cin >> name >> fn;
            mp[name] = id;
            int len = (int) fn.length();
            if (fn.back() == 'm') g = 1, fn.pop_back();
            else if (fn.back() == 'f') g = 0, fn.pop_back();
            else if (fn.back() == 'n') {
                g = 1;
                fn = fn.substr(0, len - 4);
                has_an = 1;
            } else if (fn.back() == 'r') {
                g = 0;
                fn = fn.substr(0, len - 7);
                has_an = 1;
            }
        }
    };
    vector<P> a(n);
    const int D = 20;
    vector<vi> son(n), f(n, vi(D + 1));
    for (int i = 0; i < n; i++) a[i].input(i);
    vi fa(n, -1), dep(n), o;
    for (int i = 0; i < n; i++) {
        if (a[i].has_an) {
            fa[i] = mp[a[i].fn];
            son[fa[i]].push_back(i);
        } else {
            fa[i] = i;
            dep[i] = 1;
            o.push_back(i);
        }
        f[i][0] = fa[i];
    }
    for (int i = 0; i < (int) o.size(); i++) {
        int u = o[i];
        for (int v : son[u]) {
            dep[v] = dep[u] + 1;
            o.push_back(v);
        }
    }
    for (int d = 0; d < D; d++) {
        for (int u = 0; u < n; u++) {
            f[u][d + 1] = f[f[u][d]][d];
        }
    }
    auto LCA = [&] (int u, int v) {
        if (f[u].back() != f[v].back()) return -1;
        if (dep[u] < dep[v]) swap(u, v);
        for (int d = D; ~d; d--) {
            if (int nu = f[u][d]; dep[nu] >= dep[v]) u = nu;
        }
        if (u == v) return u;
        for (int d = D; ~d; d--) {
            if (int nu = f[u][d], nv = f[v][d]; nu != nv) u = nu, v = nv;
        }
        return fa[u];
    };
    int q;
    cin >> q;
    while (q--) {
        vector<string> s(4);
        cin >> s;
        if (mp.find(s[0]) == mp.end() || mp.find(s[2]) == mp.end()) {
            cout << "NA\n";
            continue;
        }
        int u = mp[s[0]], v = mp[s[2]];
        if (a[u].fn != s[1] || a[v].fn != s[3]) {
            cout << "NA\n";
            continue;
        }
        if (a[u].g == a[v].g) {
            cout << "Whatever\n";
            continue;
        }
        int x = LCA(u, v);
        if (!~x || min(dep[u] - dep[x], dep[v] - dep[x]) >= 4) {
            cout << "Yes\n";
        } else cout << "No\n";
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
