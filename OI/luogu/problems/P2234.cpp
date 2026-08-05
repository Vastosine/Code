// Problem : P2234 [HNOI2002] 营业额统计 https://www.luogu.com.cn/problem/P2234
// Time    : 2026-08-05 18:40:25

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    long long ans = a[0];
    for (int i = 1; i < n; i++) {
        int t;
        for (t = i; t && a[t] < a[t - 1]; t--) {
            std::swap(a[t], a[t - 1]);
        }
        if (t == i) ans += a[t] - a[t - 1];
        else if (t) ans += std::min(a[t] - a[t - 1], a[t + 1] - a[t]); 
        else ans += a[1] - a[0];
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}