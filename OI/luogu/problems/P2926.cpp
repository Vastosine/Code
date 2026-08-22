// Problem : P2926 [USACO08DEC] Patting Heads S https://www.luogu.com.cn/problem/P2926
// Time    : 2026-08-19 08:59:48

#include <algorithm>
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
    struct Cow {
        int x, id;
        bool operator<(const Cow &cow) const { return x < cow.x; }
        bool operator!=(const Cow &cow) const { return x != cow.x; }
        bool operator==(const Cow &cow) const { return x == cow.x; }
    };
    cin >> n;
    vector<Cow> a(n);
    vector<int> ans(1e6 + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    std::sort(a.begin(), a.end());
    for (int l = 0; l < n; l++) {
        int r = l;
        while (a[r + 1] == a[r]) r++;
        int x = r - l, y = x + 1;
        ans[a[l].x] += x;
        for (int i = a[l].x * 2; i < 1e6 + 1; i += a[l].x) ans[i] += y;
        l = r;
    }
    vi s(n);
    for (Cow i : a) s[i.id] = ans[i.x];
    for (int i : s) cout << i << "\n";
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}