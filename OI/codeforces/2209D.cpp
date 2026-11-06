// Problem : D. Ghostfires https://codeforces.com/problemset/problem/2209/D
// Time    : 2026-11-06 10:40:21
#include <iostream>
#include <utility>
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

string map = "RGB";
vi con(vi a) {
    int n = a[0] + a[1] + a[2];
    vi ans;
    for (int i = 0; i < n; i++) {
        if (i & 1) {
            if (a[1]) a[1]--, ans.push_back(1);
            else a[2]--, ans.push_back(2);
        } else {
            a[0]--;
            ans.push_back(0);
        }
    }
    return ans;
}

string build(const vector<pii> &tr, const vi &a) {
    string ans;
    for (int x : a) {
        ans.push_back(map[tr[x].second]);
    }
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    vector<pii> a(3);
    for (int i = 0; i < 3; i++) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    Sort(a);
    swap(a[0], a[2]);
    vi c;
    for (auto &[u, v] : a) c.push_back(u);
    if (c[0] >= c[1] + c[2]) {
        return build(a, con({min(c[0], c[1] + c[2] + 1), c[1], c[2]}));
    }
    int k = c[1] + c[2] - c[0];
    vi ans = con({c[0] - k, c[1] - k, c[2] - k});
    while (k--) {
        int y = ans.empty() ? 0 : ans.back(), x = ans.empty() ? 1 : ans[ans.size() - 2], z = 3 - x - y;
        ans.push_back(x);
        ans.push_back(y);
        ans.push_back(z);
    }
    return build(a, ans);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
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