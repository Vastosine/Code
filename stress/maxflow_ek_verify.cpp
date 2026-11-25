// Verify his matrix EK (OI/template/netflow/study/maxflow_ek.cpp) against an s-t min-cut brute.
// Two families: without parallel edges, and with them (multigraph).
#define main SOL_MAIN_RENAMED
#include "../OI/template/netflow/study/maxflow_ek.cpp"
#undef main

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static const ll BIG = 1ll << 60;

static ll run_his(int n_, const vector<array<ll, 3>> &ed, int s, int t) {
    ostringstream in;
    in << n_ << " " << ed.size() << " " << s << " " << t << "\n";
    for (auto &e : ed) in << e[0] << " " << e[1] << " " << e[2] << "\n";
    istringstream is(in.str());
    ostringstream os;
    streambuf *oi = cin.rdbuf(is.rdbuf());
    streambuf *oo = cout.rdbuf(os.rdbuf());
    cin.clear();
    SOL_MAIN_RENAMED();
    cout.rdbuf(oo);
    cin.rdbuf(oi);
    cin.clear();
    istringstream got(os.str());
    ll x = 0;
    got >> x;
    return x;
}

static ll mincut(int n_, const vector<array<ll, 3>> &ed, int s, int t) {
    ll best = BIG;
    for (int mask = 0; mask < (1 << (n_ + 1)); mask++) {
        if (!((mask >> s) & 1)) continue;
        if ((mask >> t) & 1) continue;
        ll c = 0;
        for (auto &e : ed)
            if (((mask >> (int)e[0]) & 1) && !((mask >> (int)e[1]) & 1)) c += e[2];
        best = min(best, c);
    }
    return best;
}

int main() {
    // his own counterexample: must print 3
    {
        vector<array<ll, 3>> ed = {{1,2,2},{2,3,2},{1,3,4},{2,4,1},{3,4,2}};
        printf("his own example: got %lld, want 3\n", run_his(4, ed, 1, 4));
    }
    mt19937 rng(99);
    for (int family = 0; family < 2; family++) {
        long long cases = 0, bad = 0;
        for (int n_ = 2; n_ <= 7; n_++) {
            for (int tc = 0; tc < 400; tc++) {
                vector<array<ll, 3>> ed;
                set<pair<int, int>> used;
                int m_ = (int)(rng() % (3 * n_ + 2));
                for (int i = 0; i < m_; i++) {
                    int u = 1 + rng() % n_, v = 1 + rng() % n_;
                    if (u == v) continue;
                    if (family == 0 && used.count({u, v})) continue;   // simple graph
                    used.insert({u, v});
                    ed.push_back({(ll)u, (ll)v, (ll)(1 + rng() % 6)});
                }
                if (ed.empty()) continue;
                int s = 1, t = n_;
                ll want = mincut(n_, ed, s, t);
                ll got = run_his(n_, ed, s, t);
                cases++;
                if (got != want) {
                    if (bad < 4) {
                        printf("  n=%d s=%d t=%d got=%lld want=%lld   edges:", n_, s, t, got, want);
                        for (auto &e : ed) printf(" %lld->%lld(%lld)", e[0], e[1], e[2]);
                        printf("\n");
                    }
                    bad++;
                }
            }
        }
        printf("%s: %lld cases, %lld wrong\n", family == 0 ? "simple graph    " : "parallel edges  ", cases, bad);
    }
    return 0;
}
