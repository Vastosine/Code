// Problem : E. Memory Cell Interception https://codeforces.com/contest/2272/problem/E
// Time    : 2026-10-26 22:36:11
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    vi n(2);
    vector<vi> b(2), ans(2), space(2);
    vi c(2);
    vector<string> a(2);
    vector<queue<int>> q(2);
    cin >> n >> a;
    for (int i = 0; i < 2; i++) {
        b[i].assign(n[i], 0);
        for (int j = 0; j < n[i]; j++) {
            b[i][j] = a[i][j] == 'W';
        }
        for (int j = n[i] - 2; ~j; j--) {
            b[i][j] += b[i][j + 1];
        }
        for (int j = n[i] - 1; ~j; j--) {
            if (a[i][j] == 'W') break;
            c[i]++;
        }
        for (int j = n[i] - 1, cnt = (int) 1e6; ~j; j--) {
            if (a[i][j] == 'W' && cnt) {
                space[i].push_back(cnt);
                q[i].push(cnt);
                cnt = 0;
            }
            cnt += a[i][j] == 'R';
        }
    }
    for (int i = 0; i < 2; i++) {
        int t = b[!i][0] + 1;
        for (int j = 0, pre = -1; j < n[i]; j++) {
            if (a[i][j] == 'W') {
                pre = j;
                continue;
            }
            if (pre == -1) {
                ans[i].push_back(t);
                queue<int> nxt;
                while (!q[!i].empty()) {
                    int u = q[!i].front();
                    q[!i].pop();
                    if (u > 1) nxt.push(u - 1);
                    t++;
                }
                q[!i] = nxt;
            } else {
                int l = pre, r = max(pre + n[!i], b[!i][0] ? j + n[!i] - c[!i] - 1 : 0);
                ans[i].push_back(r - l + 1);
            }
        }
        cout << ans[i] << "\n";
    }
    return 0LL;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}