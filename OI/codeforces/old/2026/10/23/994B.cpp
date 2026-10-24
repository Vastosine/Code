// Problem : B. Knights of a Polygonal Table https://codeforces.com/problemset/problem/994/B
// Time    : 2026-10-23 15:50:08
#include <iostream>
#include <set>
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
    int n, m;
    cin >> n >> m;
    struct K {
        int p, c, id;
    };
    vector<K> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].p;
        a[i].id = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].c;
    }
    Sort(a, [] (const K &x, const K &y) {
        return x.p < y.p;
    });
    vector<ll> ans(n);
    multiset<ll> s;
    for (int i = 0; i < n; i++) {
        ll t = 0, c = 0;
        for (int x : s) {
            if (c >= m) break;
            t -= x;
            c++;
        }
        ans[a[i].id] = t + a[i].c;
        s.insert(-a[i].c);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    // cin >> c;
    while (c--) cout << solve() << "\n";
    // while (c--) solve();
    // const string OUT[2] = {"NO", "YES"}; while (c--) cout << OUT[solve()] << "\n";
    return 0;
}