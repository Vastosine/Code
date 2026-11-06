// Problem : C2. Disgusting + GCD (Checker Version) https://codeforces.com/contest/2284/problem/C2
// Time    : 2026-11-06 22:35:16
#include <iostream>
#include <numeric>
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
vi primes, nxt;
void init() {
    int n = 1e6, m = 1e5;
    vi is(n + 1, 1);
    is[0] = is[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (is[i]) primes.push_back(i);
        for (ll p : primes) {
            if (p * i > n) break;
            is[p * i] = 0;
            if (i % p == 0) break;
        }
    }
    nxt.assign(m + 1, 0);
    for (int i = 2, pi = 0; i <= m; i++) {
        if (is[i]) nxt[i] = i, pi++;
        else {
            int p = primes[pi];
            // cout << i << " " << p << " " << gcd(p - i, i) << "\n";
            nxt[i] = p;
        }
    }
}
int mx = 0;

auto Main([[maybe_unused]] int C = 0) {
    int a, b;
    cin >> a >> b;
    if (a == b) return vi();
    vi ans;
    // if (nxt[a] <= b && a != nxt[a]) {
    //     ans.push_back(nxt[a] - a);
    //     a = nxt[a];
    // }
    while (a < b) {
        bool k = 0;
        for (int t = b - a; t; t--) {
            if (gcd(t, a) == 1 && (t + a == b || gcd(b - t - a, a + t) == 1)) {
                a += t;
                ans.push_back(t);
                k = 1;
                break;
            }
        }
        if (!k) {
            for (int t = b - a; t ; t--) {
                if (gcd(t, a) == 1) {
                    a += t;
                    ans.push_back(t);
                    k = 1;
                    break;
                }
            }
        }
    }
    mx = max(mx, (int)ans.size());
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        cout << ans.size() << "\n" << ans << (ans.empty() ? "" : "\n");
    }
    // cerr << mx;
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 
 *  CHECK Output Format                              : 

 */