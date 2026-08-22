// Problem : P2789 直线交点数 https://www.luogu.com.cn/problem/P2789
// Time    : 2026-08-19 08:59:44

#include <iostream>
#include <set>
#include <vector>


using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

std::set<int> s;

int g(int x) { return x * (x - 1) / 2; }

int f(int x, int min = 1, int sum = 0) {
    if (!x) return s.insert(sum), 1;
    int ans = 0;
    for (int i = min; i <= x; i++) {
        ans += f(x - i, i, sum + g(i));
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    f(n);
    cout << s.size();
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}