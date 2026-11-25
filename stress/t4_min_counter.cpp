// find the SMALLEST counterexample to 4.cpp's greedy, for op=0 and op=1
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

static int N;
static vector<long long> a;

static bool conflict(int i, int j, long long k, int op) {
    long long x = a[j], y = a[i];
    if (op == 0) return x == k * y;
    return x / y == k;
}

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
                i.insert(x); t = true; p = (p + q) % sn; break;
            }
        }
        if (!t) s.push_back({}), s.back().insert(x);
    }
    return (int) s.size();
}

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

static int chrom(long long k, int op) {
    g.assign(N, {});
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (conflict(i, j, k, op)) g[i].push_back(j), g[j].push_back(i);
    int t = 1;
    while (t <= N && !canColor(t)) t++;
    return t;
}

int main() {
    for (int op = 0; op <= 1; op++) {
        bool found = false;
        for (int sz = 2; sz <= 6 && !found; sz++) {
            for (long long k = 2; k <= 6 && !found; k++) {
                // combinations of size sz from 1..30
                vector<int> idx(sz);
                for (int i = 0; i < sz; i++) idx[i] = i + 1;
                while (!found) {
                    a.clear();
                    for (int i : idx) a.push_back(i);
                    N = sz;
                    int gg = greedy(k, op), cc = chrom(k, op);
                    if (gg != cc) {
                        printf("op=%d  k=%lld  n=%d  a=", op, k, sz);
                        for (auto x : a) printf("%lld ", x);
                        printf("  greedy=%d  optimal=%d\n", gg, cc);
                        found = true;
                        break;
                    }
                    int p = sz - 1;
                    while (p >= 0 && idx[p] == 30 - (sz - 1 - p)) p--;
                    if (p < 0) break;
                    idx[p]++;
                    for (int i = p + 1; i < sz; i++) idx[i] = idx[i - 1] + 1;
                }
            }
        }
        if (!found) printf("op=%d: no counterexample with n<=6, k<=6, a<=30\n", op);
    }
    return 0;
}
