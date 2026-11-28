// Problem : P18116 [NOIP2026] 勇者 / brave（民间数据） https://www.luogu.com.cn/problem/P18116?contestId=376524
// Time    : 2026-11-28 17:20:35
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
template<typename T> void Reverse(vector<T> &a) { reverse(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename T> void Unique(vector<T> &a) { sort(a.begin(), a.end()), a.erase(unique(a.begin(), a.end()), a.end()); }
template<typename... Args> void assign(szt n, vector<Args> &...args) { (..., args.assign(n, {})); }
template<typename T> T Max(T &x, const T &y) { return x = max(x, y); } template<typename T> T Min(T &x, const T &y) { return x = min(x, y); }
int popcnt(szt x) { return __builtin_popcountll(x); }
void init() {}

vll f(vll &a) {
    szt n = a.size();
    vll ans(n);
    vector<pll> st;
    for (szt i = 0; i < n; i++) {
        while (!st.empty() && -st.back().first <= a[i]) st.pop_back();
        auto it = lower_bound(st.begin(), st.end(), pll{-a[i] * 2, 0});
        ans[i] = it == st.begin() ? -1 : (it - 1)->second;
        st.push_back({-a[i], i});
    }
    return ans;
}

auto Main(int C = 0) {
    // cerr << C;
    ll n, m;
    cin >> n >> m;
    vll a(n), s;
    auto sum = [&] (szt l, szt r) {
        if (l > r) return 0ll;
        return s[r] - (l ? s[l - 1] : 0);
    };
    vll pos(n);
    cin >> a >> pos;
    vll pre = f(a);
    Reverse(a);
    vll suf = f(a);
    Reverse(a);
    Reverse(suf);
    for (auto &i : suf) i = ~i ? n - i - 1 : -1;
    s = a;
    for (szt i = 1; i < n; i++) s[i] += s[i - 1];
    auto f = [&] (ll at, ll x, ll time) {
        szt cur = upper_bound(pos.begin(), pos.end(), x) - pos.begin();
        if (cur >= n) return at;
        if (pos[cur] - x > time) return at;
        time -= pos[cur] - x;
        ll l = cur - 1, r = cur, dir = 1;
        while (true) {
            if ((~l && at < a[l]) && at < a[r]) return at;
            if ((dir == 1 || at < a[l]) && at >= a[r]) {
                dir = 1;
                ll nxt = suf[r];
                if (!~nxt || pos[nxt] - pos[cur] > time) {
                    auto it = upper_bound(pos.begin(), pos.end(), pos[cur] + time) - pos.begin() - 1;
                    return at + sum(r, it);
                }
                time -= pos[nxt] - pos[cur];
                at += sum(r, nxt - 1);
                cur = r = nxt;
            } else {
                dir = -1;
                if (l < 0) return at;
                ll nxt = pre[l];
                if (!~nxt || pos[cur] - pos[nxt] > time) {
                    auto it = lower_bound(pos.begin(), pos.end(), pos[cur] - time) - pos.begin();
                    return at + sum(it, l);
                }
                time -= pos[cur] - pos[nxt];
                at += sum(nxt + 1, l);
                cur = l = nxt;
            }
        }
    };
    vst lst;
    while (m--) {
        ll at, x, time;
        cin >> at >> x >> time;
        lst.push_back(f(at, x, time));
    }
    return lst;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    cin >> C;
    for (int c = 0; c < C; c++) {
        [[maybe_unused]] auto ans = Main(c);
        cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
