// Problem : P1241 括号序列 https://www.luogu.com.cn/problem/P1241
// Time    : 2026-08-05 18:40:23

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

bool isLeft(char c) { return c == '(' || c == '['; }
bool match(char l, char r) { return l == '(' && r == ')' || l == '[' && r == ']';}

void solve() {
    std::string s;
    cin >> s;
    int n = s.length();
    vector<int> mat(n);
    for (int i = 0; i < n; i++) {
        if (!isLeft(s[i])) {
            std::stack<int> st;
            for (int j = i - 1; j + 1; j--) {
                if (mat[j]) continue;
                if (isLeft(s[j])) {
                    if (match(s[j], s[i])) mat[i] = mat[j] = true;  
                    break;
                }
                // else need[i] = need[j] = true;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (mat[i]) cout << s[i];
        else {
            if (s[i] == '[' || s[i] == ']') cout << "[]";
            else cout << "()";
        }
    }
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}