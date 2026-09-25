// Problem : $name$ $url$
// Time    : $date$ $time$
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
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }
template<typename... Args, typename T> void assign(int n, const T &x, vector<Args>&... args) { (..., args.assign(n, x)); }

const int NUM[10][7] = {
    {1, 1, 1, 1, 1, 1},
    {0, 1, 1},
    {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};
int MAP[10][10];

void init() {
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            int ans = 0;
            for (int k = 0; k < 7; k++) {
                ans += NUM[i][k] != NUM[j][k];
            }
            MAP[i][j] = MAP[j][i] = ans;
        }
    }
}

vi get(int x, int n) {
    vi a;
    while (x && a.size() < n) {
        a.push_back(x % 10);
        x /= 10;
    }
    while (a.size() < n) a.push_back(0);
    return a;
}

int get(int x, int y, int n) {
    vi a = get(x, n), b = get(y, n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += MAP[a[i]][b[i]];
    }
    return ans;
}

void solve() {
    init();
    int n, m;
    cin >> n >> m;
    int x;
    cin >> x;
    int ans = 0;
    // for (auto &i : MAP) {
    //     for (int j : i) cout << j << " ";
    //     cout << "\n";
    // }
    while (m--) {
        int z;
        cin >> z;
        int y = x + z;
        ans += get(x, y, n);
        x = y;
    }
    cout << ans;
}

#undef int

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}