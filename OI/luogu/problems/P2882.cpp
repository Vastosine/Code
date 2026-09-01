// Problem : P2882 [USACO07MAR] Face The Right Way G https://www.luogu.com.cn/problem/P2882
// Time    : 2026-08-31 12:20:26

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

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (int &i : a) {
        char x; 
        cin >> x;
        i = x == 'F';
    }
    int K = 0, M = n;
    for (int i = 1; i <= n; i++) {
        vi p(n);
        bool k = false;
        int ans = 0;
        for (int j = 0; j < n; j++) {
            if (j - i >= 0) k ^= p[j - i];
            ans += p[j] = k ^ !a[j];
            k ^= p[j];
            if (p[j] && i + j > n) ans = n;
        }
        if (ans < M) K = i, M = ans;
    }
    cout << K << " " << M;
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