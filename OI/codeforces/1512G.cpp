// Problem : G. Short Task https://codeforces.com/problemset/problem/1512/G
// Time    : 2026-10-31 11:11:18
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }

vi is, primes;
vector<vi> P;
set<int> can;

void init() {
    int n = 1e7 + 1;
    is.assign(n, 1);
    P.assign(n, {});
    is[0] = is[1] = 0;
    for (int i = 2; i * i < n; i++) {
        if (!is[i]) continue;
        for (int j = i * 2; j < n; j += i) {
            is[j] = 0;
        }
    }
    for (int i = 2; i < n; i++) {
        if (is[i]) {
            primes.push_back(i);
            // cout << i << "\n";
        }
    }
    for (int i = 2; i * i < n; i++) {
        if (!is[i]) continue;
        ll x = 1 + i;
        while ((x = x * i + 1) < n) {
            P[i].push_back(x);
            // if (can.find(x) != can.end() || is[x - 1]) cerr << i << " " << x;
            can.insert(x);
        }
        // cout << P[i] << "\n";
    }
}

ll qpow(ll x, ll n) {
    return n ? qpow(x * x, n / 2) * ((n & 1) ? x : 1) : 1;
}

int Main([[maybe_unused]] int C = 0) {
    int n;
    cin >> n;
    int N = n;
    if (n == 1) return 1;
    map<int, int> ps;
    for (int p : primes) {
        if (p * p > n) break;
        while (n % p == 0) ps[p]++, n /= p;
    }
    if (n > 1) ps[n]++;
    // for (auto [u, v] : ps) cout << u << " " << v << "\n";
    vector<vi> lst;
    auto dfs = [&] (auto &&f, auto it, int sum = 1) {
        if (it == ps.end()) {
            if (is[sum - 1]) {
                lst.push_back({sum, sum - 1, 1});
                return ;
            }
            if (can.find(sum) == can.end()) return ;
            if (sum == 31) {
                lst.push_back({31, 2, 4});
                lst.push_back({31, 5, 2});
                return ;
            }
            for (int p : primes) {
                if (p >= (int) P.size() || p * p > sum) return ;
                auto iter = lower_bound(P[p].begin(), P[p].end(), sum);
                if (iter != P[p].end() && *iter == sum) {
                    lst.push_back({sum, p, (int)(iter - P[p].begin()) + 2});
                    return ;
                }
            }
        }
        auto [u, v] = *it;
        it++;
        for (int i = 0; i <= v; i++, sum *= u) {
            f(f, it, sum);
        }
    };
    dfs(dfs, ps.begin());
    ll ans = N + 1;
    auto find = [&] (auto &&f, set<int> &choosen, ll x = 1, ll sum = 1, int i = 0) {
        if (sum > N) return ;
        if (sum == N || i == (int) lst.size()) {
            if (sum == N) ans = min(ans, x);
            return ;
        }
        f(f, choosen, x, sum, i + 1);
        if (choosen.find(lst[i][1]) == choosen.end()) {
            choosen.insert(lst[i][1]);
            f(f, choosen, x * qpow(lst[i][1], lst[i][2]), sum * lst[i][0], i + 1);
            choosen.erase(lst[i][1]);
        }
    };
    set<int> ch;
    find(find, ch);
    return ans == N + 1 ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
