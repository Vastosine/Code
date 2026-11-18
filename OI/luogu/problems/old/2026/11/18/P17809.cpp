// Problem : P17809 [ICPC 2019 Nanchang R] Dynamic Suffix Array https://www.luogu.com.cn/problem/P17809
// Time    : 2026-11-18 06:59:23
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
// void addEdge(int u, int v) { e[u].push_back(v); e[v].push_back(u); }
// void addEdge(int u, int v, ll w) { e[u].push_back({v, w}); e[v].push_back({u, w}); }
void init() {}

string s;
struct Trie {
    vector<vi> e, contain;
    vi siz;
    int newNode() { e.push_back(vi(26)), contain.push_back({}), siz.push_back(0); return e.size() - 1; }
    Trie() { newNode(); }

    void insert(char c) {
        int &nxt = e[0][c - 'a'];
        if (!nxt) nxt = newNode();
        contain[nxt].push_back(s.length());
        siz[nxt]++;
        siz[0]++;
        s.push_back(c);
    }

    int rank(int id) {
        int cur = 0, ans = 0, dep = 0;
        while (true) {
            if (id + dep >= (int) s.length() || siz[cur] <= 1) return ans;
            vi tmp = contain[cur];
            contain[cur].clear();
            for (int i : tmp) {
                if (i + dep >= (int) s.length()) {
                    contain[cur].push_back(i);
                    continue;
                }
                int &nxt = e[cur][s[i + dep] - 'a'];
                if (!nxt) nxt = newNode();
                contain[nxt].push_back(i);
                siz[nxt]++;
            }
            int c = s[id + dep] - 'a';
            if (!e[cur][c]) return ans;
            ans += (int) contain[cur].size();
            for (int i = 0; i < c; i++) {
                if (int nxt = e[cur][i]; nxt) ans += siz[nxt];
            }
            cur = e[cur][c];
            dep++;
        }
    }

    // int find(int x) {
    //     int cur = 0, dep = 0;
    //     while (true) {
    //         for (int i : contain[cur]) {
    //             if (i + dep >= (int) s.length()) continue;
    //             int &nxt = e[cur][s[i + dep] - 'a'];
    //             if (!nxt) nxt = newNode();
    //             contain[nxt].push_back(i);
    //             siz[nxt]++;
    //         }
    //         if (x <= (int) contain[cur].size()) return contain[cur][0];
    //         for (int i = 0; i < 26; i++) {
    //             if (int nxt = e[cur][i]; nxt) {
    //                 if (x <= siz[nxt]) {
    //                     cur = nxt;
    //                     break;
    //                 }
    //                 x -= siz[nxt];
    //             } 
    //         }
    //         dep++;
    //     }
    // }
} a;

auto Main([[maybe_unused]] int C = 0) {
    int op, x;
    char c;
    cin >> op;
    if (op == 1) {
        cin >> c;
        a.insert(c);
    } else cin >> x, cout << a.rank(x - 1) + 1 << "\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
