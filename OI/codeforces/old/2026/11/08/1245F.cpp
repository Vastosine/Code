// Problem : F. Daniel and Spring Cleaning https://codeforces.com/problemset/problem/1245/F
// Time    : 2026-11-08 19:37:20
#include <bitset>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
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

const int T = 30;

ll S(const vi &A, const vi &B) {
    vector<vector<vll>> f(T + 1, vector<vll>(2, vll(2)));
    f[0][1][1] = 1;
    for (int i = 0; i < T; i++) {
        int a = A[i];
        int b = B[i];
        for (int p = 0; p < 2; p++) {
            for (int q = 0; q < 2; q++) {
                for (int x = 2; ~x; x--) {
                    if ((x == 1 && p && !a) || (x == 2 && q && !b)) continue; 
                    f[i + 1][p && (x & 1) == a][q && (x >> 1) == b] += f[i][p][q];
                }
            }
        }
    }
    ll ans = 0;
    for (auto &i : f[T]) for (ll j : i) ans += j;
    return ans;
}

vi transfer(int x) {
    vi ans;
    for (int k = T - 1; ~k; k--) {
        ans.push_back(((1 << k) & x) > 0);
    }
    return ans;
}

// State: f[n][p][q]: n digits, p for a whether tight, q for b;
// Transfer: f[i + 1][p && x == A[i]][q && (x >> 1) == B[i]] += f[i][p][q];
//           x in [0, 2]
// Complexity: 30 * 2 * 2 * 3
// Border: f[0][1][1] = 1;
// Calculate: S(A, B) = sum of f[n]
// outer Calculate: S(r, r) - S(r, l - 1) * 2 + S(l - 1, l - 1)
auto Main([[maybe_unused]] int C = 0) {
    int l, r;
    cin >> l >> r;
    l--;
    vi q = transfer(r);
    if (l < 0) return S(q, q);
    vi p = transfer(l);
    return S(q, q) + S(p, p) - S(p, q) * 2;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
