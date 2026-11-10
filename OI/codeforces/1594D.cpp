// Problem : D. The Number of Imposters https://codeforces.com/problemset/problem/1594/D
// Time    : 2026-11-10 14:35:45
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

// vertice marks 0/1 stands for crewmate/imposter
// edge marks 0/1 stands for u say v crewmate/imposter
// so edge from u to v (if has) equals to val[u] ^ val[v]
// so color or check v equals/dose not equal to col[u] when edge from u to v is 0/1
// calculate which color is more is the answer
// calculate per connected block (view edge as undirected)
auto Main([[maybe_unused]] int C = 0) {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> e;
    vi col;
    assign(n + 1, e, col);
    int ans = 0;
    while (m--) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        int w = s == "imposter";
        e[u].push_back({v, w}); e[v].push_back({u, w});
    }
    vi o;
    vi cnt;
    for (int st = 1; st <= n; st++) {
        if (col[st]) continue;
        col[st] = 1;
        o.assign(1, st);
        cnt.assign(3, 0);
        for (int i = 0; i < (int) o.size(); i++) {
            int u = o[i];
            cnt[col[u]]++;
            for (auto &[v, w] : e[u]) {
                if (col[v]) {
                    if ((col[u] != col[v]) != w) 
                        return -1;
                } else {
                    col[v] = w ? 3 - col[u] : col[u];
                    o.push_back(v);
                }
            }
        }
        ans += max(cnt[1], cnt[2]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
