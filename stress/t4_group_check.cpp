// T4 group: brute-force chromatic number vs 4.cpp's greedy first-fit (oracle test)
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <set>
#include <vector>
using namespace std;

static int K, OP;
static vector<long long> a;

// conflict between ai < aj
static bool conflict(int i, int j) {
    long long x = a[j], y = a[i];
    if (OP == 0) return x == (long long) K * y;   // exact x/y == k
    return x / y == K;                            // floor(x/y) == k
}

// verbatim mirror of 4.cpp's grouping
static int greedy(long long k, int op) {
    vector<set<long long>> s;
    int p = 0;
    for (long long x : a) {
        bool t = false;
        int sn = (int) s.size();
        for (int q = 0; q < sn; q++) {
            auto &i = s[(p + q) % sn];
            auto it = i.upper_bound(x / (k + op) - !op);
            if (it == i.end() || x / *it != k) {
                i.insert(x);
                t = true;
                p = (p + q) % sn;
                break;
            }
        }
        if (!t) s.push_back({}), s.back().insert(x);
    }
    return (int) s.size();
}

static int n;
static vector<vector<int>> g;

static bool canColor(int t) {
    vector<int> c(n, -1);
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

int main(int argc, char **argv) {
    int trials = argc > 1 ? atoi(argv[1]) : 3000;
    mt19937 rng(20261125);
    int bad[2] = {0, 0};
    for (int tc = 0; tc < trials; tc++) {
        int op = tc & 1;
        int k = 2 + (int) (rng() % 4);
        int m = 2 + (int) (rng() % 8);
        vector<long long> pool;
        for (long long v = 1; v <= 60; v++) pool.push_back(v);
        shuffle(pool.begin(), pool.end(), rng);
        a.assign(pool.begin(), pool.begin() + m);
        sort(a.begin(), a.end());
        K = k; OP = op; n = m;
        g.assign(n, {});
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (conflict(i, j)) g[i].push_back(j), g[j].push_back(i);
        int chrom = 1;
        while (chrom <= n && !canColor(chrom)) chrom++;
        int got = greedy(k, op);
        if (got != chrom) {
            if (++bad[op] <= 5) {
                printf("OP=%d k=%d  a=", op, k);
                for (auto x : a) printf("%lld ", x);
                printf("  greedy=%d  chrom=%d\n", got, chrom);
            }
        }
    }
    printf("\nmismatches of %d trials:  op=0 -> %d   op=1 -> %d\n", trials, bad[0], bad[1]);
    return 0;
}
