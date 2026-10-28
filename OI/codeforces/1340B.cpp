// Problem : B. Nastya and Scoreboard https://codeforces.com/problemset/problem/1340/B
// Time    : 2026-10-28 11:01:40
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

int popcnt(int x) {
    return __builtin_popcount(x);
}

// 1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011
const vi T = {
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

void Max(string &x, string y) {
    x = max(x, y);
}

int steps(int from, int to) {
    int ans = 0;
    for (int t = 0; t < 7; t++) {
        int x = 1 << t;
        if ((from & x) > (to & x)) return -1;
        if ((from & x) < (to & x)) ans++;
    }
    return ans;
}

auto solve() {
    int n, k;
    cin >> n >> k;
    vi a(n), need(n + 1, 7), mx(n + 1, 0);
    need[n] = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int c : s) a[i] = a[i] * 2 + c - '0';
    }
    vector<vi> can(n + 1, vi(k + 1));
    can[n][0] = 1;
    for (int i = n - 1; ~i; i--) {
        for (int j = 0; j <= k; j++) {
            if (!can[i + 1][j]) continue;
            for (int x : T) {
                int cost = steps(a[i], x);
                if (~cost && cost + j <= k) can[i][cost + j] = 1;
            }
        }
    }
    if (!can[0][k]) return string("-1");
    string ans;
    for (int i = 0; i < n; i++) {
        for (int j = 9; ~j; j--) {
            int cost = steps(a[i], T[j]);
            if (~cost && cost <= k && can[i + 1][k - cost]) {
                ans += char(j + '0');
                k -= cost;
                break;  
            }
        }
    }
    return ans;
    // vector<vector<string>> f(2, vector<string>(k + 1, "-"));
    // f[0][0] = "";
    // for (int i = 0; i < n; i++) {
    //     for (auto &j : f[(i + 1) % 2]) j = "-";
    //     for (int j = 0; j <= k; j++) {
    //         if (f[i % 2][j] == "-") continue;
    //         for (int p = 0; p < 10; p++) {
    //             int x = T[p];
    //             int nxt = j, can = 1;
    //             for (int pos = 0; pos < 7; pos++) {
    //                 int q = 1 << pos;
    //                 if ((x & q) < (a[i] & q)) {
    //                     can = 0;
    //                     break;
    //                 }
    //                 if ((x & q) > (a[i] & q)) nxt++;
    //             }
    //             if (can && nxt <= k) Max(f[(i + 1) % 2][nxt], f[i % 2][j] + (char)(p + '0'));
    //         }
    //     }
    // }
    // return f[n % 2][k] == "-" ? "-1" : f[n % 2][k];
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}