#include <iostream>
#include <stack>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::stack;

string solve(const string &s, const vector<int> &map, int l, int r) {
    string ans;
    for (int i = l; i < r; i++) {
        if (s[i] == '[') {
            int y = map[i];
            int x = s[++i] - '0';
            if (s[++i] <= '9') x = x * 10 + s[i++] - '0';
            string ss = solve(s, map, i, y);
            while (x--) ans += ss;
            i = y;
        } else {
            ans += s[i];
        }
    }
    return ans;
}

int main() {
    string s;
    cin >> s;
    int n = s.length();
    vector<int> map(n);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '[') st.push(i);
        if (s[i] == ']') {
            map[st.top()] = i;
            st.pop();
        }
    }
    cout << solve(s, map, 0, n);
}