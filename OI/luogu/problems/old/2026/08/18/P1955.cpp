// Problem : P1955 [NOI2015] 程序自动分析 https://www.luogu.com.cn/problem/P1955
// Time    : 2026-08-18 11:26:08

#include <iostream>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::unordered_map;
unordered_map<int, int> f;

int getFa(int x) {
    if (f.find(x) == f.end()) return f[x] = x;
    return f[x] == x ? x : f[x] = getFa(f[x]);
}

void merge(int u, int v) {
    f[getFa(v)] = getFa(u);
}

void solve() {
    int n;
    cin >> n;
    f.clear();
    vector<pii> check;
    while (n--) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w) merge(u, v);
        else check.push_back({u, v});
    }
    for (pii i : check) {
        if (getFa(i.first) == getFa(i.second)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}