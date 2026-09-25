// Problem : T806146 「TPOI-2B」AND and Subsequence https://www.luogu.com.cn/problem/T806146?contestId=163680
// Time    : 2026-08-29 14:00:52

#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::set;

int solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    a.push_back(0);
    set<pii> s;
    for (int i = 0; i < 31; i++) {
        int l = -1;
        for (int j = 0; j <= n; j++) {
            bool k = a[j] & (1 << i);
            if (k && l < 0) l = j;
            if (!k && l >= 0) s.insert({l, j - 1}), l = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        auto it = s.lower_bound({i, i});
        vector<pii> t;
        while (it != s.end() && it->first == i) {
            t.push_back(*it);
            it++;
        }
        if (t.size() < 2) {
            continue;
        }
        int r = t[0].second;
        for (int j = 1; j < t.size(); j++) {
            s.erase(t[j]);
            s.insert({r + 1, t[j].second});
        }
    }
    return s.size();
}

int main() {
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}