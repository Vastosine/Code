// What is the largest chromatic number this conflict graph ever needs?
#include <algorithm>
#include <cstdio>
#include <random>
#include <set>
#include <vector>
using namespace std;

static int N;
static vector<long long> a;
static vector<vector<int>> g;

static bool canColor(int t) {
    vector<int> c(N, -1);
    struct H {
        static bool go(int u, int t, vector<int> &c, const vector<vector<int>> &g) {
            if (u == (int) c.size()) return true;
            for (int x = 0; x < t; x++) {
                bool ok = true;
                for (int v : g[u]) if (c[v] == x) { ok = false; break; }
                if (!ok) continue;
                c[u] = x;
                if (go(u + 1, t, c, g)) return true;
                c[u] = -1;
            }
            return false;
        }
    };
    return H::go(0, t, c, g);
}

int main() {
    mt19937_64 rng(1125);
    int hist[2][8] = {};
    int maxc[2] = {0, 0};
    for (int tc = 0; tc < 12000; tc++) {
        int op = tc & 1;
        long long k = 2 + (long long) (rng() % 3);
        int m = 3 + (int) (rng() % 9);
        long long hi = (long long) pow(2.0, rng() % 20) + 40;   // wide value range
        vector<long long> pool;
        for (long long v = 1; v <= hi; v++) pool.push_back(v);
        shuffle(pool.begin(), pool.end(), rng);
        a.assign(pool.begin(), pool.begin() + m);
        sort(a.begin(), a.end());
        N = m;
        g.assign(N, {});
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++) {
                long long x = a[j], y = a[i];
                bool c = op == 0 ? (x == k * y) : (x / y == k);
                if (c) g[i].push_back(j), g[j].push_back(i);
            }
        int t = 1;
        while (t <= N && !canColor(t)) t++;
        hist[op][t]++;
        maxc[op] = max(maxc[op], t);
    }
    printf("op=0   max chi = %d   histogram(1..):", maxc[0]);
    for (int i = 1; i <= 4; i++) printf("  %d:%d", i, hist[0][i]);
    printf("\nop=1   max chi = %d   histogram(1..):", maxc[1]);
    for (int i = 1; i <= 4; i++) printf("  %d:%d", i, hist[1][i]);
    printf("\n");
    return 0;
}
