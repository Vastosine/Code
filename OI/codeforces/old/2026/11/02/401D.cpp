// Problem : D. Roman and Numbers https://codeforces.com/problemset/problem/401/D
// Time    : 2026-11-02 11:00:03
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

auto Main([[maybe_unused]] int C = 0) {
    ll n, M;
    cin >> n >> M;
    vi s(10), w(11, 1);
    while (n) {
        s[n % 10]++;
        n /= 10;
    }
    for (int i = 1; i <= 10; i++) w[i] = w[i - 1] * (1 + s[i - 1]);
    vector<vector<ll>> f(w[10], vector<ll>(M));
    f[0][0] = 1;
    for (int i = 0; i < w[10]; i++) {
        for (int j = 0; j < M; j++) {
            if (!f[i][j]) continue;
            for (int x = 0; x < 10; x++) {
                if (!i && !x) continue;
                if (i / w[x] % (s[x] + 1) == s[x]) continue;
                f[i + w[x]][(j * 10 + x) % M] += f[i][j];
            }
        }
    }
    return f.back()[0];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
