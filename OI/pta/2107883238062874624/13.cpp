// Problem : $name$ $url$
// Time    : $date$ $time$
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

bool is_c(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

const vector<string> sp = {"if", "else", "for", "while"};

auto Main([[maybe_unused]] int C = 0) {
    char SSS[350];
    cin.getline(SSS, 349);
    string s = SSS;
    vector<string> ans;
    int pos = 0;
    while (true) {
        while (s[pos] == ' ') pos++;
        if (s.substr(pos, 2) == "if" && !is_c(s[pos + 2])) {

        }
        int ed = s.find_first_of(";", pos);
    }
    return 0;
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */