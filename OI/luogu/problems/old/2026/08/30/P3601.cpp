// Problem : P3601 签到题 https://www.luogu.com.cn/problem/P3601
// Time    : 2026-08-30 10:40:25

#include <iostream>
#include <vector>
#include <cmath>

#define int long long

using std::cin;
using std::cout;
using std::vector;
using std::string;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

const int M = 666623333;

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

vi primes = getPrimes(1e6 + 1);

int phi(int x) {
    int ans = x;
    for (int p : primes) {
        if (p > x) break;
        if (x % p) continue;
        while (x % p == 0) x /= p;
        ans = ans / p * (p - 1);
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans;
}

void solve() {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    vi ans(n);
    for (int i = l; i <= r; i++) {
        ans[i - l] = i;
    }
    vi x = ans;
    for (int p : primes) {
        for (int i = (p - (l % p)) % p; i < n; i += p) {
            ans[i] = ans[i] / p * (p - 1);
            while (x[i] % p == 0) x[i] /= p;
        }
    }
    for (int i = l; i <= r; i++) {
        if (x[i - l] > 1) ans[i - l] = ans[i - l] / x[i - l] * (x[i - l] - 1);
        ans[i - l] = i - ans[i - l];
    }
    int out = 0;
    for (int i : ans) (out += i) %= M;
    cout << out;
}

#undef int

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}