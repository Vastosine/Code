#include <iostream>
#include <string>
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

string Main([[maybe_unused]] int C = 0) {
    string s;
    while (s.empty()) getline(cin, s);
    int p1 = s.find_first_of(','), p2 = s.find_first_of('.');
    if (p1 == string::npos || p2 == string::npos || p1 < 3 || p2 < 3) return "Skipped";
    if (string s1 = s.substr(p1 - 3, 3), s2 = s.substr(p2 - 3, 3); s1 == "ong" && s2 == "ong") {
        vector<string> a;
        for (int p = 0; p < p2; ) {
            int q = s.find_first_of(" .", p);
            a.push_back(s.substr(p, q - p + 1));
            p = q + 1;
        }
        int len = a.size();
        if (len < 3) return "Skipped";
        a.back() = "zhong.";
        a[len - 2] = "ben ";
        a[len - 3] = "qiao ";
        string ans;
        for (auto &i : a) ans += i;
        return ans;
    }
    return "Skipped";
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
