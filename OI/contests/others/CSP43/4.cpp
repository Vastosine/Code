#include <cstdlib>
#include <iostream>
#include <set>
#include <unordered_map>
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
    ll n, k, op;
    cin >> n >> k >> op;
    vll a(n);
    cin >> a;
    Sort(a);
    if (op == 0) {
        set<ll> p, q;
        for (ll x : a) {
            if (x % k == 0 && p.find(x / k) != p.end()) q.insert(x);
            else p.insert(x);
        }
        if (q.empty()) cout << 1 << "\n" << p.size() << " " << vll(p.begin(), p.end());
        else cout << 2 << "\n" << p.size() << " " << vll(p.begin(), p.end()) << "\n" << q.size() << " " << vll(q.begin(), q.end()); 
        return 0;
    }
    auto check = [&] () -> bool {
        set<ll> s(a.begin(), a.end());
        unordered_map<ll, int> col;
        vector<vll> res(2);
        while (!s.empty()) {
            vll o(1, *s.begin());
            s.erase(s.begin());
            for (int i = 0; i < (int) o.size(); i++) {
                ll u = o[i];
                vll lst;
                res[col[u]].push_back(u);
                for (auto it = s.upper_bound(u / (k + 1)); it != s.end() && u / *it == k; it++) {
                    lst.push_back(*it);
                }
                for (auto it = s.lower_bound(u * k); it != s.end() && *it / u == k; it++) {
                    lst.push_back(*it);
                }
                for (ll x : lst) {
                    col[x] = col[u] ^ 1;
                    s.erase(x);
                    o.push_back(x);
                }
            }
        }
        Sort(res[0]);
        Sort(res[1]);
        if (res[1].empty()) res.pop_back();
        for (auto &t : res) {
            for (auto &i : t) {
                auto it = upper_bound(t.begin(), t.end(), i / (k + 1));
                if (it != t.end() && i / *it == k) return false;
            }
        }
        cout << res.size() << "\n";
        for (auto &t : res) {
            cout << t.size() << " ";
            for (auto &i : t) {
                cout << i << " ";
            }
            cout << "\n";
        }
        return true;
    };
    if (check()) return 0;
    vector<set<ll>> s;
    int p = 0;
    for (ll x : a) {
        bool t = false;
        int sn = (int) s.size();
        for (int q = 0; q < sn; q++) {
            auto &i = s[(p + q) % sn];
            if (auto it = i.upper_bound(x / (k + 1)); it == i.end() || x / *it != k) {
                i.insert(x);
                t = true;
                p = (p + q) % sn;
                break;
            }
        }
        if (!t) s.push_back({}), s.back().insert(x);
    }
    cout << s.size() << "\n";
    for (auto &i : s) {
        cout << i.size() << " ";
        for (auto &j : i) cout << j << " ";
        cout << "\n";
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
