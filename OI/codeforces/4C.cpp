// Problem : C. Registration system https://codeforces.com/problemset/problem/4/C
// Time    : 2026-10-23 11:46:34
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll NEG = -(1LL << 60); [[maybe_unused]] const ll INF = (1LL << 60);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }


auto solve() {
    int n;
    cin >> n;
    map<string, int> a;
    while (n--) {
        string s;
        cin >> s;
        if (a.find(s) == a.end()) cout << "OK\n", a[s] = 1;
        else for (int i = a[s]; ; i++) {
            string t = s + to_string(i);
            if (a.find(t) == a.end()) {
                cout << t << "\n";
                a[t] = 1;
                a[s]++;
                break;
            }
        }
    }
    return 1;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    // while (c--) cout << solve() << "\n";
    while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}