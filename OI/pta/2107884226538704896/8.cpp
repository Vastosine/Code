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

auto Main([[maybe_unused]] int C = 0) {
    string in;
    while (in.empty()) getline(cin, in);
    // 1
    cout << in << "\n";
    vector<string> ans;
    // 2
    for (int pos = 0; pos < (int) in.size(); ) {
        pos = in.find_first_not_of(" ", pos);
        if (pos == -1) break;
        int nxt = in.find_first_of(" ", pos);
        if (nxt == -1) {
            ans.push_back(in.substr(pos));
            break;
        }
        ans.push_back(in.substr(pos, nxt - pos));
        pos = nxt + 1;
    }
    // 3 6
    for (auto &s : ans) {
        for (auto &x : s) {
            if (x != 'I' && x >= 'A' && x <= 'Z') x += 'a' - 'A';
            if (x == '?') x = '!';
        }
    }
    // 4 5
    for (int i = 0; i < (int) ans.size(); i++) {
        if (i && ans[i] == "you" && (ans[i - 1] == "can" || ans[i - 1] == "could")) {
            ans[i] = "I";
            swap(ans[i], ans[i - 1]);
        } else if (ans[i] == "I" || ans[i] == "me") {
            ans[i] = "you";
        } else if (ans[i][0] == 'I' && (ans[i][1] < 'a' || ans[i][1] > 'z') && ans[i][1] != 'I') {
            ans[i] = "you" + ans[i].substr(1);
        }
    }
    cout << "AI: ";
    int len = (int) ans.size();
    for (int i = 0; i < len; i++) {
        cout << ans[i] ;
        if (i < len - 1) {
            int c = ans[i + 1][0];
            if ((c >= 'a' && c <= 'z') || c == 'I' || (c >= '0' && c <= '9')) cout << " ";
        }
    }
    cout << "\n";
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
