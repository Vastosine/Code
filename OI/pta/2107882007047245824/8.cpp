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

struct Matric {
    int n, m;
    vector<vi> a;
    Matric(int n = 0, int m = 0) : n(n), m(m), a(n, vi(m)) {}

    void input() {
        cin >> n >> m;
        a.assign(n, vi(m));
        cin >> a;
    }

    vi &operator[](int x) { return a[x]; }
    const vi &operator[](int x) const { return a[x]; }

    Matric operator*(const Matric &b) const {
        if (m != b.n) return {};
        Matric ans(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return ans;
    }
};

auto Main([[maybe_unused]] int C = 0) {
    Matric a, b;
    a.input();
    b.input();
    Matric ans = a * b;
    if (ans.a.empty()) {
        cout << "Error: " << a.m << " != " << b.n << "\n";
    } else {
        cout << ans.n << " " << ans.m << "\n";
        for (auto &i : ans.a) {
            for (int j = 0; j < (int) i.size(); j++) {
                if (j) cout << " ";
                cout << i[j];
            }
            cout << "\n";
        }
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
