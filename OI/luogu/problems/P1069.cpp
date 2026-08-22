// Problem : P1069 [NOIP 2009 普及组] 细胞分裂 https://www.luogu.com.cn/problem/P1069
// Time    : 2026-08-19 08:59:52

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

vi pr;
int pn;

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
        if (is[i]) pr.push_back(i);
    }
    pn = pr.size();
}

vi factorize(int x, int k = 1) {
    vi ans(pn);
    for (int i = 0; i < pn; i++) {
        int p = pr[i];
        if (p > x) break;
        while (!(x % p)) x /= p, ans[i] += k;
    }   
    if (x > 1) ans.push_back(x);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    init();
    int x0, y0;
    cin >> x0 >> y0;
    vi x = factorize(x0, y0);
    unsigned ans = -1;
    for (int i = 0; i < n; i++) {
        unsigned a, y = 0;
        cin >> a;
        vi b = factorize(a);
        for (int j = 0; j < pn; j++) {
            if (!x[j]) continue;
            if (!b[j]) {
                y = -1;
                break;
            }
            y = std::max(y, unsigned(x[j] - 1) / b[j] + 1);
        }
        ans = std::min(ans, (unsigned)y);
    }
    cout << (int)ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}