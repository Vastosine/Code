// Problem : P1072 [NOIP 2009 提高组] Hankson 的趣味题 https://www.luogu.com.cn/problem/P1072
// Time    : 2026-08-19 08:59:52

#include <iostream>
#include <set>
#include <vector>
#define int long long

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vi pr, PR;
std::set<int> pset, PSET;
int pn, PN;

void init() {
    const int maxn = 5e4;
    pr.clear();
    vi is(maxn, 1);
    for (int i = 2; i * i < maxn; i++) {
        if (!is[i]) continue;
        for (int j = i * 2; j < maxn; j += i) {
            is[j] = false;
        }
    }
    for (int i = 2; i < maxn; i++) {
        if (is[i]) pr.push_back(i), pset.insert(i);
    }
    PN = pn = pr.size();
    PR = pr;
    PSET = pset;
}

vi factorize(int x) {
    vi ans(pn);
    for (int i = 0; i < pn; i++) {
        int p = pr[i];
        if (p > x) break;
        while (!(x % p)) x /= p, ans[i]++;
    }   
    if (x > 1) ans.push_back(x);
    return ans;
}

void solve() {
    // pr = PR, pn = PN, pset = PSET;
    while (pn != PN) {
        pset.erase(pr.back());
        pr.pop_back();
        pn--;
    }
    vi a(4);
    vector<vi> b(4);
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
        b[i] = factorize(a[i]);
        if (b[i].size() > pn && pset.find(b[i].back()) == pset.end()) {
            pr.push_back(b[i].back());
            pset.insert(b[i].back());
            // cout << b[i].back();
        }
    }
    pn = pr.size();
    for (int i = 0; i < 4; i++) {
        b[i] = factorize(a[i]);
    }
    int ans = 1;
    for (int i = 0; i < pn; i++) {
        int l1 = b[1][i], l2 = l1, r2 = b[3][i], r1 = r2;
        if (b[1][i] != b[0][i]) r1 = b[1][i];
        if (b[3][i] != b[2][i]) l2 = b[3][i];
        if (l1 > r2 || l2 > r1) return cout << 0 << "\n", void();
        int l = std::max(l1, l2), r = std::min(r1, r2);
        ans *= r - l + 1;
    }
    cout << ans << "\n";
}

#undef int

int main() {
    init();
    int c = 1;
    cin >> c;
    while (c--) solve();
    return 0;
}