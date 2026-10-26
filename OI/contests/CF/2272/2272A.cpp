// Problem : A. Maximize One MEX https://codeforces.com/contest/2272/problem/A
// Time    : 2026-10-26 22:36:08
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

int f(const vi &a, int k) {
    int n = (int) a.size();
    vi b, vis(n + 1);
    int ans = 0;
    for (int i : a) {
        vis[i]++;
        while (vis[ans]) ans++;
        b.push_back(ans);
    }
    Sort(b);
    return b[n - k];
}

vi solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    int ans = f(a, k);
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(a[i], a[j]);
            int y;
            if ((y = f(a, k)) > ans) {
                ans = y;
                l = i;
                r = j;
            }
            swap(a[i], a[j]);
        }
    }
    return l < 0 ? vi{-1} : vi{l + 1, r + 1};
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}