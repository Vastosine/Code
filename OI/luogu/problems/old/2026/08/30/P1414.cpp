// Problem : P1414 又是毕业季II https://www.luogu.com.cn/problem/P1414
// Time    : 2026-08-29 11:10:09

#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::sort;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vi getPrimes(int max) {
    vector<bool> is(max + 1, true);
    vi ans;
    for (int i = 2; i * i <= max; i++) {
        if (is[i]) {
            for (int j = i * 2; j <= max; j += i) {
                is[j] = false;
            } 
        }
    }
    for (int i = 2; i <= max; i++) {
        if (is[i]) ans.push_back(i);
    }
    return ans;
}

void dfs(vi &count, const vector<pii> &ps, int i = 0, int x = 1) {
    if (i == ps.size()) return count[x]++, void();
    int u = ps[i].first, v = ps[i].second;
    for (int j = 0; j <= v; j++) {
        dfs(count, ps, i + 1, x);
        x *= u;
    }
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    sort(a.begin(), a.end(), [](int x, int y) { return x > y; });
    vi primes = getPrimes(a.front()), count(a.front() + 1, 0);
    for (int i : a) {
        vector<pii> ps;
        for (int p : primes) {
            int x = 0;
            while (i % p == 0) i /= p, x++;
            if (x) ps.push_back({p, x});
            if (i == 1) break;
        }
        dfs(count, ps);
    }
    vi ans(n + 1, 0);
    for (int i = 0; i <= a.front(); i++) {
        ans[count[i]] = i;
    }
    int max = 0;
    for (int i = n; i; i--) {
        max = ans[i] = std::max(max, ans[i]);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}