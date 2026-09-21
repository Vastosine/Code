// Problem : P2216 [HAOI2007] 理想的正方形 https://www.luogu.com.cn/problem/P2216
// Time    : 2026-09-01 17:31:14

#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> void sort(vector<T> &a) { std::sort(a.begin(), a.end()); }
template<typename T, typename C> void sort(vector<T> &a, C cmp) { std::sort(a.begin(), a.end(), cmp); }

using std::deque;

void solve() {
    int n, m, r;
    cin >> n >> m >> r;
    vector<vi> a(n, vi(m)), ca = a, cb = a;
    cin >> a;
    for (int i = 0; i < m; i++) {
        deque<int> qa, qb;
        for (int j = 0; j < n; j++) {
            while (!qa.empty() && a[qa.back()][i] <= a[j][i]) qa.pop_back();
            while (!qb.empty() && a[qb.back()][i] >= a[j][i]) qb.pop_back();
            qa.push_back(j);
            qb.push_back(j);
            if (qa.front() <= j - r) qa.pop_front();
            if (qb.front() <= j - r) qb.pop_front();
            if (j >= r - 1) {
                ca[j - r + 1][i] = a[qa.front()][i], 
                cb[j - r + 1][i] = a[qb.front()][i];
            }
        }
    }
    // for (vi &i : cb) {
    //     for (int j : i) cout << j << " ";
    //     cout << "\n";
    // }
    int ans = 0x7fffffff;
    for (int i = 0; i + r <= n; i++) {
        deque<int> qa, qb;
        for (int j = 0; j < m; j++) {
            while (!qa.empty() && ca[i][qa.back()] <= ca[i][j]) qa.pop_back();
            while (!qb.empty() && cb[i][qb.back()] >= cb[i][j]) qb.pop_back();
            qa.push_back(j);
            qb.push_back(j);
            if (qa.front() <= j - r) qa.pop_front();
            if (qb.front() <= j - r) qb.pop_front();
            if (j >= r - 1) {
                ans = std::min(ans, ca[i][qa.front()] - cb[i][qb.front()]);
            }
        }
    }
    cout << ans;
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