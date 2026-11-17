// Problem : P4147 玉蟾宫 https://www.luogu.com.cn/problem/P4147
// Time    : 2026-09-01 17:31:10

#include <iostream>
#include <vector>
#include <algorithm>

// #define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

#define f(k) ((s[k][0] - j + 1) * s[k][1])

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    cin >> a;
    vi mx(m);
    int ans = 0;
    vector<vi> d(n, vi(m));
    for (int i = n - 1; i + 1; i--) {
        vector<vi> s;
        for (int j = m - 1, k = 0; j + 1; j--) {
            mx[j] = (a[i][j] == 'F') * (1 + mx[j]);
            if (!mx[j]) {
                s.clear();
                continue;
            }
            s.push_back({j, mx[j]});
            for (int l = s.size() - 1; l + 1 && s[l][1] >= mx[j]; l--) {
                s[l][1] = mx[j];
                while (l + 1 < s.size()) s.pop_back();
                k = 0;
            }
            for (int K = k + 1; K < s.size(); K++) {
                if (f(K) > f(k)) k = K;
            }
            // while (!s.empty() && mx[s.back()[1]] > mx[j]) s.pop_back();
            // if (k >= s.size()) k = std::max(s.size(), 1ull) - 1;
            while (k + 1 < s.size() && f(k) < f(k + 1)) k++;
            d[i][j] = f(k);
            // if (d[i][j] == 64) std::cerr << i << " " << j << "\n";
            ans = std::max(ans, d[i][j]);
        }
    }
    // for (int i = 620; i < n; i++) {
    //     for (int j = 595; j < m; j++) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // for (vi &i : d) {
    //     for (int j : i) cout << j << "\t";
    //     cout << "\n";
    // }
    // cout << d[624][597];
    cout << ans * 3;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}