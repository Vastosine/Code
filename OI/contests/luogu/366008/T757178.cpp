// Problem : T757178 [ICPC 2019 Nanchang R] And and Pair https://www.luogu.com.cn/problem/T757178?contestId=366008
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

const int M = 1e9 + 7;
vector<ll> pow2;

void init() {
    int n = 1e5 + 5;
    pow2.assign(n, 0);
    pow2[0] = 1;
    for (int i = 1; i < n; i++) {
        pow2[i] = pow2[i - 1] * 2 % M;
    }
}

auto Main(int C = 0) {
    string s;
    cin >> s;
    int n = (int) s.length();
    vi a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[n - i - 1] - '0';
    }
    vector<ll> f(n);
    ll ans = 0;
    for (ll i = 0, pre = 0; i < n; i++, pre = pre%M * 2) {
        if (!a[i]) {
            continue;
        }
        f[i] = (pow2[i] + pre / 2) % M;
        (pre += f[i]) %= M;
        (ans += f[i]) %= M;
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
