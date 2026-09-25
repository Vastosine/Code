// Problem : T452219 「TPOI-2C」Secret Illumination https://www.luogu.com.cn/problem/T452219?contestId=163680
// Time    : 2026-08-29 14:00:55

#include <iostream>
#include <vector>
#define int long long

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

void solve() {
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        while (n--) cout << "1 ";
        cout << "\n";
        return;
    }
    if (k < 2 || n < 2) return cout << "-1\n", void();
    if (k <= 1e9) {
        cout << "1 " << k;
        for (int i = 2; i < n; i++) {
            cout << " 1";
        }
        cout << "\n";
        return;
    }
    vi a(n, 1);
    const int N = 1e9;
    int max = N + 1, K = k;
    int id = n - 1;
    while (max-- && id > 1 && k > max) {
        int x = std::min(max, k / id);
        // if (k - x * id == 1) x--;
        if (x <= 1) continue;
        k -= x * id;
        a[id] = x;
        id--;
    }
    if (k > 1 && k <= max) a[1] = k, k = 0;
    // if (k && a[1] == 1 &&  a[2] == 1) {
    //     if (k == 7 && max >= 3) {
    //         a[1] = 3;
    //         a[2] = 2;
    //         k = 0;
    //     }
    // }
    if (k) return cout << "-1\n", void();
    for (int j : a) cout << j << " ";
    cout << "\n";
    int check = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > 1) check += a[i] * i;
    }
    std::cerr << (check == K) << "\n";
}

#undef int

int main() {
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}