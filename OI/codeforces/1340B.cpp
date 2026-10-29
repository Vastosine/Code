// Problem : B. Nastya and Scoreboard https://codeforces.com/problemset/problem/1340/B
// Time    : 2026-10-29 08:19:16
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

const int T[] = {
    0b1110111,
    0b0010010,
    0b1011101,
    0b1011011,
    0b0111010,
    0b1101011,
    0b1101111,
    0b1010010,
    0b1111111,
    0b1111011
};

int need(int fr, int to) {
    int ans = 0;
    for (int k = 1; k < (1 << 7); k <<= 1) {
        if ((fr & k) > (to & k)) return -1;
        if ((fr & k) < (to & k)) ans++;
    }
    return ans;
}

auto solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (int &i : a) {
        string s;
        cin >> s;
        for (char c : s) {
            i = i * 2 + c - '0';
        }
    }
    vector<vi> can(n + 1, vi(k + 1)); 
    can[n][0] = 1;
    for (int i = n; i; i--) {
        for (int j = 0; j <= k; j++) {
            if (!can[i][j]) continue;
            for (int x : T) {
                int nxt = need(a[i - 1], x);
                if (nxt == -1) continue;
                nxt += j;
                if (nxt <= k) can[i - 1][nxt] = 1;
            }
        }
    }
    if (!can[0][k]) return string("-1");
    string ans;
    for (int i = 0; i < n; i++) {
        for (int j = 9; ~j; j--) {
            int x = T[j];
            int nxt = need(a[i], x);
            if (nxt == -1) continue;
            if (nxt <= k && can[i + 1][k - nxt]) {
                ans.push_back(j + '0');
                k -= nxt;
                break;
            }
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO,
    // YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}