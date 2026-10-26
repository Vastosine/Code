// brute reference for 1946C (Tree Cutting) -- enumerate every set of k edges.
//   input : t, then per case "n k" and n-1 edges   (same as the real problem)
//   output: maximum possible minimum component size
// Only for small n: C(n-1, k) subsets, each checked in O(n).
#include <bits/stdc++.h>
using namespace std;

static int n, k;
static vector<pair<int, int>> ed;
static vector<int> par;

static int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        ed.resize(n - 1);
        for (auto &e : ed) cin >> e.first >> e.second;

        int best = 0;
        int m = n - 1;
        // enumerate all masks with exactly k bits set
        for (int mask = 0; mask < (1 << m); mask++) {
            if (__builtin_popcount((unsigned)mask) != k) continue;
            par.resize(n + 1);
            for (int i = 1; i <= n; i++) par[i] = i;
            for (int i = 0; i < m; i++) {
                if (mask >> i & 1) continue;  // this edge is cut
                int a = find(ed[i].first), b = find(ed[i].second);
                if (a != b) par[a] = b;
            }
            vector<int> sz(n + 1, 0);
            for (int i = 1; i <= n; i++) sz[find(i)]++;
            int mn = INT_MAX;
            for (int i = 1; i <= n; i++)
                if (sz[i]) mn = min(mn, sz[i]);
            best = max(best, mn);
        }
        cout << best << "\n";
    }
    return 0;
}
