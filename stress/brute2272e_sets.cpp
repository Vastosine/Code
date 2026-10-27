// 2272E: same brute as brute2272e.cpp, but prints the SET of values each READ
// can see instead of just the count.  Use it to look for structure.
//   input : t, then per case n m, s, t
//   output (debug, not judge format):
//     case 1  s="R" t="RWRW"
//       s[0] : 0 2 4
//       t[0] : 0
#include <bits/stdc++.h>
using namespace std;

static int n, m;
static string s, t;
static vector<set<long long>> seenA, seenB;
static int ia, ib;
static long long cellVal;

static void run(int i, int j, int ts) {
    if (i == n && j == m) return;
    if (i < n) {
        int sa = ia, sb = ib;
        long long old = cellVal;
        if (s[i] == 'W') cellVal = ts + 1;
        else seenA[ia++].insert(cellVal);
        run(i + 1, j, ts + 1);
        ia = sa; ib = sb; cellVal = old;
    }
    if (j < m) {
        int sa = ia, sb = ib;
        long long old = cellVal;
        if (t[j] == 'W') cellVal = ts + 1;
        else seenB[ib++].insert(cellVal);
        run(i, j + 1, ts + 1);
        ia = sa; ib = sb; cellVal = old;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc, cs = 0;
    cin >> tc;
    while (tc--) {
        cin >> n >> m >> s >> t;
        seenA.assign((int)count(s.begin(), s.end(), 'R'), {});
        seenB.assign((int)count(t.begin(), t.end(), 'R'), {});
        ia = ib = 0;
        cellVal = 0;
        run(0, 0, 0);

        cout << "case " << ++cs << "  s=\"" << s << "\" t=\"" << t << "\"\n";
        for (size_t i = 0; i < seenA.size(); i++) {
            cout << "  s[" << i << "] :";
            for (long long v : seenA[i]) cout << " " << v;
            cout << "\n";
        }
        for (size_t i = 0; i < seenB.size(); i++) {
            cout << "  t[" << i << "] :";
            for (long long v : seenB[i]) cout << " " << v;
            cout << "\n";
        }
    }
    return 0;
}
