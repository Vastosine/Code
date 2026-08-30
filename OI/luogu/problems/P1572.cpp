// Problem : P1572 计算分数 https://www.luogu.com.cn/problem/P1572
// Time    : 2026-08-29 11:10:07

#include <iostream>
#include <ostream>
#include <vector>
#include <bits/stl_algo.h>

using std::cin;
using std::cout;
using std::vector;
typedef vector<int> vi;
typedef std::pair<int, int> pii;
template<typename T> std::istream &operator>>(std::istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }
    using std::ostream;

class Factory {
  public:
    Factory(int x = 0, int y = 1) : a(x), b(y) {
        simplify();
    }

    Factory operator+(const Factory &factory) const {
        int y = lcm(b, factory.b);
        int x = y / this->b * this->a + y / factory.b * factory.a;
        return Factory(x, y).simplify();
    }

    Factory operator-() const {
        return Factory(-a, b).simplify();
    }

    Factory operator-(const Factory &factory) const { return *this + -factory; }

    Factory &operator+=(const Factory &factory) { return *this = *this + factory; }
    Factory &operator-=(const Factory &factory) { return *this = *this - factory; }

    friend ostream &operator<<(ostream &out, const Factory &factory) {
        out << factory.a;
        if (factory.b != 1) out <<  "/" << factory.b;
        return out;
    }

  private:
    int a;
    unsigned b;

    static int gcd(int x, int y) {
        return std::__gcd(abs(x), abs(y));
    }

    static int lcm(int x, int y) {
        return x / gcd(x, y) * y;
    }

    Factory &simplify() {
        int z = gcd(a, b);
        if (z > 1) a /= z, b /= z;
        if (b < 0) b = -b, a = -a;
        return *this;
    }
};

using std::string;

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    Factory ans;
    for (int i = 0; i < n;) {
        int x = 0, y = 1, *p = &x, op = 1;
        do {
            if (s[i] == '-') op = -1;
            else if (s[i] == '/') *(p = &y) = 0;
            else if (s[i] >= '0' && s[i] <= '9') (*p *= 10) += s[i] - '0';
            i++;
        } while (i < n && s[i] != '+' && s[i] != '-');
        ans += Factory(x * op, y);
    }
    cout << ans;
}

int main() {
    int c = 1;
    // cin >> c;
    while (c--) solve();
    return 0;
}