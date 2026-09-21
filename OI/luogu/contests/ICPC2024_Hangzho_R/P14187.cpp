// Problem : P14187 [ICPC 2024 Hangzhou R] AUS https://www.luogu.com.cn/problem/P14187?contestId=281894
// Time    : 2026-09-20 17:30:23

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

int get(vi &f, int x) {
    return f[x] = f[x] == x ? x : get(f, f[x]);
}

void merge(vi &f, int u, int v) {
    f[get(f, u)] = get(f, v);
}

bool solve() {
    string s[3];
    cin >> s[0] >> s[1] >> s[2];
    if (s[0].size() != s[1].size()) return false;
    if (s[0].size() != s[2].size()) return true;
    vi f(26);
    for (int i = 0; i < 26; i++) f[i] = i;
    for (int i = 0; i < s[0].size(); i++) {
        if (s[0][i] != s[1][i]) merge(f, s[0][i] - 'a', s[1][i] - 'a');
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < s[i].size(); j++) {
            s[i][j] = get(f, s[i][j] - 'a') + 'a';
        }
    }
    return s[0] != s[2];
}

#undef int

const string OUT[2] = {"NO", "YES"};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << OUT[solve()] << "\n";
    return 0;
}