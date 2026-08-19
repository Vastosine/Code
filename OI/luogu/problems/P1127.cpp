// Problem : P1127 词链 https://www.luogu.com.cn/problem/P1127
// Time    : 2026-08-18 17:47:33

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

using std::string;
int n;
vector<string> a;
vi vis;
string ans;

bool dfs(int i, char st = 0) {
    if (i == n) return true;
    for (int j = 0; j < n; j++) {
        if (vis[j]) continue;
        if (st && st != a[j].front()) continue;
        vis[j] = true;
        if (dfs(i + 1, a[j].back())) {
            if (i < n - 1) ans = a[j] + '.' + ans;
            else ans = a[j];
            return true;
        }
        vis[j] = false;
    }
    return false;
}

void solve() {
    cin >> n;
    a.assign(n, "");
    vis.assign(n, 0);
    cin >> a;
    int begin[26]{}, end[26]{};
    for (string &i : a) {
        begin[i.front() - 'a']++;
        end[i.back() - 'a']++;
    }
    std::sort(a.begin(), a.end());
    int k = 0;
    int st;
    for (int i = 0; i < 26; i++) {
        k += abs(begin[i] - end[i]);
        if (begin[i] > end[i]) st = i;
        // if (begin[i] < end[i]) ed = i;
    }
    if (k > 2) return cout << "***", void();
    if (dfs(0, k ? (st + 'a') : 0)) cout << ans;
    else cout << "***";
    // string ans;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (vis[j]) continue;
    //         if (k && i == 0 && a[j].front() != st + 'a') continue;
    //         if (i && ans.back() != a[j].front()) continue;
    //         if (!ans.empty()) ans += '.';
    //         ans += a[j];
    //         vis[j] = true;
    //         break;
    //     }
    // }
    // cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}