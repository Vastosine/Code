
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
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

auto Main(int a, int b) {
    if (a == b) return vi();
    vi ans;
    // if (nxt[a] <= b && a != nxt[a]) {
    //     ans.push_back(nxt[a] - a);
    //     a = nxt[a];
    // }
    while (a < b) {
        for (int t = b - a; ; t--) {
            if (gcd(t, a) == 1) {
                a += t;
                ans.push_back(t);
                break;
            }
        }
    }
    return ans;
}


static mt19937_64 rng;

static ll rnd(ll lo, ll hi) { return lo + (ll)(rand() % (unsigned long long)(hi - lo + 1)); }

int a = 74458;
int b = 74489;

auto check([[maybe_unused]] int C = 0) {
    a = rnd(2, 1000);
    b = a + rnd(0, 100);
    int A = a;
    auto ans = Main(A, b);
    if (ans.size() > 3) return false;
    for (int i : ans) {
        if (gcd(i, A) != 1) return false;
        A += i;
    }
    return A == b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1000000;
    // cin >> C;
    auto seed = time(0);
    srand(seed);
    cerr << seed << "\n";
    cerr << a << "\n";
    for (int c = 0; c < C; c++) {
        if (!check(c)) {
            cerr << a << " " << b << "\n";
            return -1;
        }
        // [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    // return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 
 *  CHECK Output Format                              : 

 */