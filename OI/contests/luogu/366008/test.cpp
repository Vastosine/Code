// Problem : T757177 [ICPC 2019 Nanchang R] A Funny Bipartite Graph https://www.luogu.com.cn/problem/T757177?contestId=366008
// Time    : 2026-10-29 13:00:07
#include <iostream>
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
const int M = 1e9 + 7;

auto Main(int C = 0) {
    string s;
    cin >> s;
    ll x = 0;
    for (int i : s) x = x * 2 + i - '0';
    ll ans = 0;
    for (ll mask = x; mask; mask = (mask - 1) & x) {
        ll t = 1;
        for (ll k = 1; k <= mask; k *= 2) {
            if (!(k & mask)) t *= 2;
        }
        ans += t;
    }
    return (ans + 1) % M;
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
