#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std; typedef long long ll; typedef vector<bool> vb; typedef vector<int> vi; typedef vector<ll> vll; typedef pair<int, int> pii; typedef pair<ll, ll> pll;
typedef unsigned long long szt; typedef vector<szt> vst; typedef pair<szt, szt> pst;
[[maybe_unused]] const ll INF = 1ll << 60; [[maybe_unused]] const int inf = 0x3fffffff;
template<typename A, typename B> istream &operator>>(istream &in, pair<A, B> &a) { return in >> a.first >> a.second; }
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

bool isSub(const vst &s, const vst &t, szt pos) {
    if (t.size() > s.size() - pos) return false;
    for (szt i = 0; i < t.size(); i++) {
        if (s[i + pos] != t[i]) return false;
    }
    return true;
}

auto Main(int = 0) {
    szt n, m;
    cin >> n;
    vst a(n);
    cin >> a >> m;
    vector<pair<vst, szt>> b(m);
    for (szt i = 0; i < m; i++) {
        auto &X = b[i];
        szt k;
        cin >> k;
        X.first.assign(k, 0);
        cin >> X.first;
        X.second = i;
    }
    Sort(b, [] (auto &x, auto &y) { return x.first < y.first; });
    vb use(m);
    vst ans;
    auto f = [&] (auto &&f, szt cur = 0) {
        if (cur == n - 1) {
            return true;
        }
        szt p = lower_bound(b.begin(), b.end(), pair<vst, int>{{a[cur]}, 0}) - b.begin();
        for (szt i = p; i < n; i++) {
            if (!use[i] && isSub(a, b[i].first, cur)) {
                use[i] = 1;
                if (f(f, cur + b[i].first.size() - 1)) {
                    ans.push_back(b[i].second);
                    return true;
                }
                use[i] = 0;
            }
        }
        return false;
    };
    f(f);
    for (szt i = ans.size() - 1; ~i; i--) {
        cout << ans[i] + 1 << " \n"[!i];
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
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
