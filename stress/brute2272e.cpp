// brute reference for 2272E (Memory Cell Interception).
//   input : t, then per case n m, s, t     (same as the real problem)
//   output: per case, two lines: counts for the R's of s, then for the R's of t
//
// Enumerates every interleaving (n, m <= 5) and collects, for each READ, the
// set of values it can see.
#include <bits/stdc++.h>
using namespace std;

static int n, m;
static string s, t;
static vector<set<long long>> seenA, seenB;  // per READ index
static int ia, ib;
static long long cellVal;

static void run(int i, int j, int ts) {
    if (i == n && j == m) return;
    // execute s[i]
    if (i < n) {
        int sa = ia, sb = ib;
        long long oldCell = cellVal;
        char c = s[i];
        if (c == 'W') cellVal = ts + 1;
        else seenA[ia++].insert(cellVal);
        run(i + 1, j, ts + 1);
        ia = sa; ib = sb; cellVal = oldCell;
    }
    // execute t[j]
    if (j < m) {
        int sa = ia, sb = ib;
        long long oldCell = cellVal;
        char c = t[j];
        if (c == 'W') cellVal = ts + 1;
        else seenB[ib++].insert(cellVal);
        run(i, j + 1, ts + 1);
        ia = sa; ib = sb; cellVal = oldCell;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m >> s >> t;
        int ca = (int)count(s.begin(), s.end(), 'R');
        int cb = (int)count(t.begin(), t.end(), 'R');
        seenA.assign(ca, {});
        seenB.assign(cb, {});
        ia = ib = 0;
        cellVal = 0;
        run(0, 0, 0);

        for (int i = 0; i < ca; i++) cout << seenA[i].size() << (i + 1 == ca ? '\n' : ' ');
        for (int i = 0; i < cb; i++) cout << seenB[i].size() << (i + 1 == cb ? '\n' : ' ');
    }
    return 0;
}
