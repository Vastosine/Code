// Problem : D. Array Differentiation https://codeforces.com/problemset/problem/1552/D
// Time    : 2026-10-30 14:44:36
#include <iostream>
#include <map>
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
    
int n;
vector<ll> a;
map<ll, int> s;

void dfs(int i = 0, ll sum = 0) {
    if (i == (int) a.size()) {
        s[sum]++;
        return;
    }
    dfs(i + 1, sum); 
    dfs(i + 1, sum + a[i]);
}

auto Main([[maybe_unused]] int C = 0) {
    cin >> n;
    a.assign(n, 0);
    cin >> a;
    s.clear();
    dfs();
    for (auto &[x, y] : s) {
        if (y > 1) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
