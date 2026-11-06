// Problem : C1. Disgusting + GCD (Constructive Version) https://codeforces.com/contest/2284/problem/C1
// Time    : 2026-11-06 22:35:16
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
    int mx = 0;
    for (int i = 2, pi = 0; i <= m; i++) {
        if (is[i]) nxt[i] = i, pi++;
        else {
            int p = primes[pi];
            // cout << i << " " << i - p << "\n";
            mx = max(mx, p - i);
            if (p - i == 71) cerr << i << " " << p << "\n";
            nxt[i] = p;
        }
    }
    cerr << mx;
}

auto Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    for (int &i : a) i = nxt[i];
    return a;
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

/**

 *  CHECK Type int * int, int to ll, negative index  : 1
 *  CHECK Vector Size                                : 1
 *  CHECK Multiple Test Clear                        : 1
 *  CHECK Restriction Value remain, border, negative : 1
 *  CHECK Output Format                              : 1

 */