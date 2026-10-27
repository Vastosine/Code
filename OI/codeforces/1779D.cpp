// Problem : D. Boris and His Amazing Haircut https://codeforces.com/problemset/problem/1779/D
// Time    : 2026-10-27 13:07:10
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args>&... args) { (..., args.assign(n, {})); }

auto solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    cin >> a >> b;
    int m;
    cin >> m;
    vi c(m), use(n);
    cin >> c;
    stack<int> s;
    map<int, int> cost;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) return false;
        while (!s.empty() && b[s.top()] < b[i]) s.pop();
        if (!s.empty() && b[s.top()] == b[i]) {
            if (!use[s.top()] && a[i] > b[i]) use[s.top()] = 1, cost[b[i]]++;
        } else {
            s.push(i);
            if (a[i] > b[i]) use[i] = 1, cost[b[i]]++;
        }
    }
    for (int i : c) {
        cost[i]--;
    }
    for (auto &[p, q] : cost) {
        if (q > 0) return false;
    }
    return true;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    // while (c--) cout << solve() << "\n";
    // while (c--) solve();
    const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}