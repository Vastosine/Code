// Problem : Fraction and Six https://m1.codeforces.com/contest/2278/problem/A
// Time    : 2026-10-31 22:37:42
#include <iostream>
#include <vector>
#include <algorithm>
#define cautor const auto &
#define autor auto &
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

bool check(char c) {
    return c == 's' || c == 'i' || c == 'x';
}

auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    string p, q;
    cin >> n >> m >> p >> q;
    if (n - m != 3) return false;
    vi c(26);
    for (cautor i : p) c[i - 'a']++;
    for (cautor i : q) c[i - 'a']--; 
    for (int i = 0; i < 26; i++) {
        if (check(i + 'a')) {
            if (c[i] != 1) return false;
        } else if (c[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
