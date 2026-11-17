// Problem : P3405 [USACO16DEC] Cities and States S https://www.luogu.com.cn/problem/P3405
// Time    : 2026-08-18 11:26:00

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
using std::string;

int hash(string s) {
    int ans = 0;
    for (int i : s) {
        (ans *= 26) += i - 'A';
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<string> s(n), S(n);
    vector<int> t(26 * 26 * 26 * 26);
    for (int i = 0; i < n; i++) {
        string str;
        cin >> s[i] >> str;
        s[i] = s[i].substr(0, 2) + str;
        a[i] = hash(s[i]);
        S[i] = s[i].substr(2, 2) + s[i].substr(0, 2);
        if (hash(s[i]) != hash(S[i]))
            t[a[i]]++;
    }
    int ans = 0;
    for (string i : S) {
        ans += t[hash(i)];
    }
    cout << ans / 2;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}