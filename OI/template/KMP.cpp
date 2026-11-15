#include <iostream>
#include <string>
#include <vector>
using namespace std;

using vi = vector<int>;

vi getNext(const string &s) {
    int n = (int) s.length();
    vi nxt(n);
    for (int i = 1; i < n; i++) {
        int x = nxt[i - 1];
        while (x && s[x] != s[i]) x = nxt[x - 1];
        nxt[i] = x + (s[x] == s[i]);
    }
    return nxt;
}

vi KMP(string s, string t) {
    int n = (int) s.length(), m = (int) t.length();
    vi nxt = getNext(t);
    vi ans;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != t[j]) j = nxt[j - 1];
        if (s[i] == t[j]) j++;
        if (j == m) j = nxt[j - 1], ans.push_back(i - m + 1);
    }
    return ans;
}

int main() {
    string s, t;
    cin >> s >> t;
    vi nxt = getNext(t);
    vi ans = KMP(s, t);
    for (int i : ans) cout << i + 1 << "\n";
    for (int i : nxt) cout << i << " ";
} 