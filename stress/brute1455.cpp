// brute reference for 1455D (Sequence and Swaps) -- BFS over states.
//   input : t, then per case "n x" and n numbers   (same as the real problem)
//   output: minimum number of swaps, or -1
// Only for small n and small values: the state is (whole array, x).
#include <bits/stdc++.h>
using namespace std;

static int n;
static bool sorted(const vector<int> &a) {
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> n >> x;
        vector<int> a(n);
        for (auto &v : a) cin >> v;

        // key = a[0..n-1] (base 11) followed by x
        auto key = [&](const vector<int> &v, int xx) {
            string s;
            for (int i = 0; i < n; i++) { s.push_back((char)('a' + v[i])); }
            s.push_back((char)('a' + xx));
            return s;
        };

        unordered_map<string, int> dist;
        queue<pair<vector<int>, int>> q;
        q.push({a, x});
        dist[key(a, x)] = 0;
        int ans = -1;

        while (!q.empty()) {
            auto [cur, cx] = q.front();
            q.pop();
            int d = dist[key(cur, cx)];
            if (sorted(cur)) { ans = d; break; }
            for (int i = 0; i < n; i++) {
                if (cur[i] <= cx) continue;
                vector<int> nxt = cur;
                swap(nxt[i], cx);
                string k = key(nxt, cx);
                if (dist.count(k)) { swap(nxt[i], cx); continue; }
                dist[k] = d + 1;
                q.push({nxt, cx});
                swap(nxt[i], cx);   // restore cx for the next iteration
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
