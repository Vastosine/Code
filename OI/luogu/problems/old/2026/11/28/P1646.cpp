// Problem : P1646 [国家集训队] happiness https://www.luogu.com.cn/problem/P1646
// Time    : 2026-11-28 11:56:08
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? " " : "") << a[i]; return out; }
template<typename T> ostream &operator<<(ostream &out, const vector<vector<T>> &a) { for (szt i = 0; i < a.size(); i++) out << (i ? "\n" : "") << a[i]; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}


class HLPP {
  public:
    // 0-index
    HLPP(szt n) : n(n), e(n) {}

    void resize(szt N) { n = N, e.resize(n); }
    void reassign() { clear(n); }
    void clear(szt N = 0) { n = N; e.assign(N, {}); to.clear(); cap.clear(); }
    szt addEdge(szt u, szt v, szt c) { add(u, v, c); add(v, u, 0); return to.size() - 2; }
    void eraseEdge(szt id) { cap[id] = cap[id ^ 1] = 0; }

    // Run the HLPP, return the max flow.
    szt run(szt s, szt t) {
        vst dis(n, ~0ull), gap(n * 2);
        auto bfs = [&] () {
            dis[t] = 0;
            vst o(1, t);
            for (szt i = 0; i < o.size(); i++) {
                szt u = o[i];
                gap[dis[u]]++;
                for (szt j : e[u]) {
                    if (szt v = to[j]; !~dis[v] && cap[j ^ 1]) {
                        o.push_back(v), dis[v] = dis[u] + 1;
                    }
                }
            }
        };
        bfs();
        if (!~dis[s]) return 0;
        dis[s] = n;
        vst excess(n), cur(n);
        vb active(n);
        vector<vst> bucket(n * 2);
        excess[s] = INF;
        szt h = 0;
        auto activate = [&] (szt u) { 
            if (!active[u] && u != s && u != t) {
                active[u] = true; 
                bucket[dis[u]].push_back(u);
                h = max(h, dis[u]);
            }
        };
        // Return weather u has excess.
        auto push = [&] (szt u) {
            for (; cur[u] < e[u].size(); cur[u]++) {
                if (szt i = e[u][cur[u]], v = to[i]; ~dis[v] && dis[v] < dis[u] && cap[i]) {
                    szt stream = min(excess[u], cap[i]);
                    if (v != s) excess[v] += stream;
                    if (u != s) excess[u] -= stream;
                    cap[i] -= stream;
                    cap[i ^ 1] += stream;
                    activate(v);
                    if (!excess[u]) return false;
                }
            }
            return true;
        };
        push(s);
        while (h) {
            if (!h) break;
            szt u = bucket[h].back();
            active[u] = false;
            bucket[h].pop_back();
            while (push(u)) {
                szt d = dis[u];
                cur[u] = 0;
                if (gap[d] == 1) {
                    for (szt i = 0; i < n; i++) {
                        if (dis[i] < n && dis[i] >= d) {
                            gap[dis[i]]--;
                            dis[i] = n + 1;
                            gap[dis[i]]++;
                            cur[i] = 0;
                        }
                    }
                } else {
                    gap[d]--;
                    d = 2 * n - 1;
                    for (szt i : e[u]) {
                        if (szt v = to[i]; cap[i] && u != v && ~dis[v]) {
                            d = min(d, dis[v] + 1);
                        }
                    }
                    gap[d]++;
                    dis[u] = d;
                }
                
            }
            while (h && bucket[h].empty()) h--;
        }
        return excess[t];
    }

    szt flowOn(szt id) const { return cap[id ^ 1]; }

  protected:
    // Add single edge
    void add(szt u, szt v, szt c) { e[u].push_back(to.size()); to.push_back(v); cap.push_back(c); };

    szt n;
    vector<vst> e;
    vst cap;
    vst to;
};

// wr 12:13
auto Main(int = 0) {
    szt n, m;
    cin >> n >> m;
    auto f = [&] (szt x, szt y) {
        return x * m + y;
    };
    szt s = n * m + 2 * (n - 1) * m + 2 * n * (m - 1), t = s + 1, N = t + 1, cnt = n * m;
    HLPP g(N);
    szt sum = 0;
    for (szt i = 0; i < n; i++) {
        for (szt j = 0; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            g.addEdge(s, f(i, j), x);
        }
    }
    for (szt i = 0; i < n; i++) {
        for (szt j = 0; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            g.addEdge(f(i, j), t, x);
        }
    }
    for (szt i = 1; i < n; i++) {
        for (szt j = 0; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            szt p = cnt++;
            g.addEdge(s, p, x);
            g.addEdge(p, f(i, j), INF);
            g.addEdge(p, f(i - 1, j), INF);
        }
    }
    for (szt i = 1; i < n; i++) {
        for (szt j = 0; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            szt p = cnt++;
            g.addEdge(p, t, x);
            g.addEdge(f(i, j), p, INF);
            g.addEdge(f(i - 1, j), p, INF);
        }
    }
    for (szt i = 0; i < n; i++) {
        for (szt j = 1; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            szt p = cnt++;
            g.addEdge(s, p, x);
            g.addEdge(p, f(i, j), INF);
            g.addEdge(p, f(i, j - 1), INF);
        }
    }
    for (szt i = 0; i < n; i++) {
        for (szt j = 1; j < m; j++) {
            szt x;
            cin >> x;
            sum += x;
            szt p = cnt++;
            g.addEdge(p, t, x);
            g.addEdge(f(i, j), p, INF);
            g.addEdge(f(i, j - 1), p, INF);
        }
    }
    return sum - g.run(s, t);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
