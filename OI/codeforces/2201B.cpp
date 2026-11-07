// Problem : B. Recollect Numbers https://codeforces.com/problemset/problem/2201/B
// Time    : 2026-11-06 10:23:25
#include <iostream>
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

vi f(int x) {
    if (x == 1) return {1, 1};
    vi ans = {1, 2};
    for (int i = 3; i <= x; i++) {
        ans.push_back(i);
        ans.push_back(i - 2);
    }
    ans.push_back(x - 1);
    ans.push_back(x);
    return ans;
}

auto Main([[maybe_unused]] int C = 0) {
    int n, k;
    cin >> n >> k;
    if (k < n || k >= n * 2) return vi();
    int p = k - n + 1;
    vi ans = f(p);
    for (int i = p + 1; i <= n; i++) {
        ans.push_back(i);
        ans.push_back(i);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}

/**

 *  CHECK Type int * int, int to ll, negative index  : 
 *  CHECK Vector Size                                : 
 *  CHECK Multiple Test Clear                        : 
 *  CHECK Restriction Value remain, border, negative : 

 */