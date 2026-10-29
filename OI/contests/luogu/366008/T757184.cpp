// Problem : T757184 [ICPC 2019 Nanchang R] Resistance https://www.luogu.com.cn/problem/T757184?contestId=366008
// Time    : 2026-10-29 13:00:10
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
using namespace std; typedef long long ll; typedef vector<int> vi; typedef pair<int, int> pii;
[[maybe_unused]] const ll INF = 1ll << 60, NEG = -INF;
template<typename T> istream &operator>>(istream &in, vector<T> &a) { for (T &x : a) in >> x; return in; }
template<typename T> ostream &operator<<(ostream &out, const vector<T> &a) { for (const T &x : a) out << x << " "; return out; }
template<typename T> void Sort(vector<T> &a) { sort(a.begin(), a.end()); }
template<typename T, typename C> void Sort(vector<T> &a, C cmp) { sort(a.begin(), a.end(), cmp); }
template<typename... Args> void assign(int n, vector<Args> &...args) { (..., args.assign(n, {})); }
void init() {}

int dis(const pii &a) {
    return a.first * a.first + a.second * a.second;
}

int dis(const pii &a, const pii &b) {
    return dis({a.first - b.first, a.second - b.second});
}

ostream &operator<<(ostream &out, const pii &p) {
    return out << "(" << p.first << "," << p.second << ")";
}

auto Main(int C = 0) {
    int n, k, L, E, T;
    cin >> n >> k >> L >> E >> T;
    vector<pii> a(L);
    for (auto &[u, v] : a) cin >> u >> v;
    int r1, d1, t1, r2, d2, t2, d3;
    cin >> r1 >> d1 >> t1 >> r2 >> d2 >> t2 >> d3;
    r1 *= r1, r2 *= r2;
    int hp[2], def;
    cin >> hp[0] >> hp[1] >> def;
    struct Defender {
        int type, x, y, use;
    };
    vector<Defender> d(k);
    for (auto &[t, x, y, c] : d) {
        cin >> t >> x >> y;
        c = -(1 << 30);
    }
    struct Eme {
        int hp, f, def, die, suc;
        bool can_choose() {
            return !~die && !~suc;
        }
    };
    vector<Eme> e(E);
    string s;
    cin >> s;
    for (int i = 0; i < E; i++) {
        e[i] = { hp[s[i] - '1'], 0, s[i] == '2' ? def : 0, -1, -1};
    }

    for (int t = 0; t < T; t++) {
        for (auto &x : e) {
            if (!x.can_choose()) continue;
            if (x.f) {
                x.f--;
                x.hp -= d3;
            }
        }
        for (auto &[type, x, y, use] : d) {
            if (type == 1 && t - use < t1) continue;
            int nearest = -1, di = 1 << 30;
            for (int i = 0; i <= t; i++) {
                int D;
                if (e[i].can_choose() && (D = dis(a[t - i], {x, y})) < di) nearest = i, di = D;
            }
            int r = type == 1 ? r1 : r2, damage = type == 1 ? d1 : d2;
            if (di <= r) {
                use = t;
                e[nearest].hp -= max(1, damage - e[nearest].def);
                if (type == 2) e[nearest].f = t2;
            }
        }
        for (int i = 0; i < E; i++) {
            auto &x = e[i];
            if (!x.can_choose()) continue;
            if (x.hp < 0) {
                x.die = t + 1;
            } else if (t - i + 1 == L) x.suc = t + 1;
        }
    }
    cout << "Case #" << C + 1 << ":\n";
    for (int i = 0; i < E; i++) {
        auto &x = e[i];
        if (x.can_choose()) {
            cout << "Be alive at " << a[T - i - 1] << " with " << x.hp << " HP(s).\n";
        } else if (~x.die) {
            cout << "Be killed in the " << x.die << "-th frame at " << a[x.die - i - 1] << ".\n";
        } else {
            cout << "Arrive with " << x.hp << " HP(s).\n";
        }
   }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string OUT[2] = {"NO", "YES"}; init(); int C = 1;
    cin >> C;
    for (int c = 0; c < C; c++) {
        auto ans = Main(c);
        // cout << ans << "\n";
        // cout << OUT[ans] << "\n";
        // ans.empty() ? cout << OUT[0] << "\n" : cout << OUT[1] << "\n" << ans << "\n";
    }
    return 0;
}
