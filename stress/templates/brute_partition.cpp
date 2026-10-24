// Brute force template: PARTITION / GROUPING (DFS + backtracking)
//
// Use when the answer is "split the elements into groups" and the group
// structure matters:
//   - buy items in groups of exactly k (pay the max of the group)
//   - split people into teams
//   - matching / pairing problems
//
// n <= 9 or so: the number of set partitions is Bell(9) = 21147, Bell(10) = 115975.
//
// Here each element either joins an existing group or opens a new one
// ("restricted growth string": this visits every partition exactly once,
// no duplicates -- do NOT permute inside a group afterwards).
//
// Copy this file to ..\brute.cpp and edit the marked places.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = (1LL << 60) | (1LL << 30); [[maybe_unused]] const ll NEG = (3LL << 62) | (3LL << 30);
template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &x) { for (const T &i : x) out << i << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }

int n, groupSize;              // groupSize = k in "groups of exactly k"
vi a;
vector<vi> groups;
ll ans = NEG;

// ---- EDIT: cost of one finished group --------------------------------
ll groupCost(const vi &g) {
    if ((int) g.size() == groupSize) return *max_element(g.begin(), g.end());  // pay the max
    if ((int) g.size() == 1) return g[0];                                      // single item
    return INF;                                                                // forbidden size
}

ll totalCost() {
    ll s = 0;
    for (auto &g : groups) s += groupCost(g);
    return s;
}

auto solve() {
    cin >> n >> groupSize;     // ---- EDIT: read n, k the way the problem gives them
    a.assign(n, 0);
    cin >> a;

    ans = NEG;
    groups.clear();
    auto dfs = [&](auto &&self, int i) -> void {
        if (i == (int) a.size()) {
            // ---- EDIT: accept / reject the finished partition ----------
            // 要最小花费就把下面的 max 改成 min
            ll c = totalCost();
            if (c < INF) ans = max(ans, c);
            return;
        }
        for (int g = 0; g < (int) groups.size(); g++) {
            groups[g].push_back(a[i]);
            self(self, i + 1);
            groups[g].pop_back();
        }
        groups.push_back({a[i]});
        self(self, i + 1);
        groups.pop_back();
    };
    dfs(dfs, 0);
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int c = 1;
    cin >> c;
    while (c--) cout << solve() << "\n";
    return 0;
}
