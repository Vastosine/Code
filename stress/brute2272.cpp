// brute reference for 2272C (Yet Another Black Cell Problem).
//   input : t, then per case "n x" and the sorted a[]   (same as the real problem)
//   output: minimum k
//
// Model: choose extra cells E (|E| <= x); S = a + E must be coverable by pairs
// at distance <= k.  An edge cover of S exists iff no cell of S is isolated in
// the "distance <= k" graph, so feasibility(k) = "exists E, |E| <= x, no
// isolated cell in S".
//
// Only for tiny inputs: enumerate every E inside [0, maxA + k].
#include <bits/stdc++.h>
using namespace std;

static int n, x;
static vector<int> a;

static bool feasible(int k, const vector<int> &E) {
    vector<int> s = a;
    for (int e : E) s.push_back(e);
    sort(s.begin(), s.end());
    for (size_t i = 0; i < s.size(); i++) {
        bool ok = false;
        if (i > 0 && s[i] - s[i - 1] <= k) ok = true;
        if (i + 1 < s.size() && s[i + 1] - s[i] <= k) ok = true;
        if (!ok) return false;
    }
    return true;
}

static bool existsWith(int k, int lo, int hi, int left, vector<int> &E) {
    if (feasible(k, E)) return true;
    if (left == 0) return false;
    for (int p = lo; p <= hi; p++) {
        if (find(a.begin(), a.end(), p) != a.end()) continue;
        if (find(E.begin(), E.end(), p) != E.end()) continue;
        E.push_back(p);
        if (existsWith(k, p + 1, hi, left - 1, E)) { E.pop_back(); return true; }
        E.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> x;
        a.resize(n);
        for (auto &v : a) cin >> v;

        int ans = -1;
        for (int k = 1; k <= 40 && ans < 0; k++) {
            vector<int> E;
            int hi = a.back() + k;              // extras never need to go further
            if (hi > 60) hi = 60;
            if (existsWith(k, 0, hi, x, E)) ans = k;
        }
        cout << ans << "\n";
    }
    return 0;
}
