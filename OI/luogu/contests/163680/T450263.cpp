// Problem : T450263 「TPOI-2A」Min Mex https://www.luogu.com.cn/problem/T450263?contestId=163680
// Time    : 2026-08-29 14:00:51

#include <algorithm>
#include <iostream>
#include <vector>
#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::sort;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    sort(a.begin(), a.end());
    int min = 1, ans = 0;
    for (int i : a) {
        if (min == k) {
            if (i > k) return ans;
            if (k == 1) return -1;
            if (i == k) min--;
        }
        if (i > min) ans += i - min;
        if (i >= min) min++;
    }
    if (min == k) return ans;
    return -1;
}

#undef int

int main() {
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}