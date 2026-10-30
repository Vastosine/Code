// Problem : F. Magic Will Save the World https://codeforces.com/problemset/problem/1862/F
// Time    : 2026-10-30 15:16:47
#include <iostream>
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
void init() {}

auto Main([[maybe_unused]] int C = 0) {
    ll n, w, f, sum = 0;
    cin >> w >> f >> n;
    vi a(n);
    cin >> a;
    for (ll i : a) {
        sum += i;
    }
    vi can(sum + 1), lst = {0};
    can[0] = 1;
    for (int x : a) {
        int m = (int) lst.size();
        for (int i = 0; i < m; i++) {
            int nxt = lst[i] + x;
            if (!can[nxt]) {
                can[nxt] = 1;
                lst.push_back(nxt);
            }
        }
    }
    auto check = [&] (int t) {
        ll x = t * w, y = t * f;
        if (x + y < sum) return false;
        if (x >= sum || y >= sum) return true;
        for (int i = sum - y; i <= x; i++) {
            if (can[i]) return true;
        }
        return false;
    };
    int l = sum / (w + f) - 1, r = sum / max(w, f) + 1;
    while (l < r - 1) {
        int x = (l + r) >> 1;
        if (check(x)) r = x;
        else l = x;
    }
    return r;
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
