// Problem : P2814 家谱 https://www.luogu.com.cn/problem/P2814
// Time    : 2026-08-18 11:26:11

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::string;
std::map<string, string> f;

string getFa(const string &s) { return s == f[s] ? s : f[s] = getFa(f[s]); }

void solve() {
    char c;
    string fa;
    while (cin >> c) {
        if (c == '#') {
            cin >> fa;
            if (f.find(fa) == f.end()) f[fa] = fa;
        } else {
            string s;
            cin >> s;
            if (c == '+') f[s] = getFa(fa);
            else cout << s + " " + getFa(s) + "\n";
        } 
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}