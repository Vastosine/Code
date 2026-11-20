#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
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

auto Main([[maybe_unused]] int C = 0) {
    struct Per {
        string name, iden;
        int status, h, m, id = 0, last = -(1 << 30), day = 0, use = 0, i;
        int f() const {
            return ((day * 24 + h) * 60 + m);
        }
        bool operator<(const Per &p) const {
            // if (day < p.day) return true;
            // if (day > p.day) return false;
            return f() < p.f() || (f() == p.f() && id < p.id);
        }
    };
    int D, P;
    cin >> D >> P;
    map<string, Per> a;
    int cnt = 0;
    set<pair<int, string>> q;
    set<string> Q;
    for (int d = 0; d < D; d++) {
        int n, m;
        cin >> n >> m;
        while (n--) {
            string name;
            cin >> name;
            a[name].name = name;
            cin >> a[name].iden >> a[name].status;
            a[name].day = d;
            scanf("%d:%d", &a[name].h, &a[name].m);
            a[name].id = ++cnt;
            a[name].use = 0;
            if (!a[name].i) a[name].i = a.size();
            if (a[name].status && a[name].iden.length() == 18 && Q.find(name) == Q.end()) q.insert({cnt, name}), Q.insert(name);
        }
        vector<Per> lst;
        for (auto &[name, p] : a) {
            if (p.iden.length() != 18 || p.last + P >= d || p.use || p.day != d) continue;
            lst.push_back(p);
        }
        Sort(lst);
        for (auto &p : lst) {
            if (!m) break;
            m--;
            cout << p.name << " " << p.iden << "\n";
            a[p.name].last = d;
            a[p.name].use = 1;
        }
    }
    for (auto [i, name] : q) {
        cout << name << " " << a[name].iden << "\n";
    }
    return 0;
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    // cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
