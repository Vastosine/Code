#ifndef __BIG_INT__
#define __BIG_INT__

#include <istream>
#include <ostream>
#include <vector>
#include <string>


class BigInt {
  public:
    typedef unsigned long long size_t;
    typedef std::string string;
    BigInt() = default;
    template<typename T> BigInt(T x) { set(x); }
    template<typename T> BigInt operator=(T x) { return set(x), *this; }
    
    template<typename T>
    void set(T x) {
        clear();
        if (x < 0) x = -x, sig = true;
        while (x) a.push_back(x % MOD), x /= MOD;
    }

    void set(const string &s) {
        clear();
        if (s[0] == '-') sig = true;
        size_t n = s.length() - sig;
        a.assign((n - 1) / BASE + 1, 0);
        for (size_t i = (n - 1) / BASE, j = sig; i + 1; i--) {
            do {
                (a[i] *= 10) += s[j++] - '0';
            } while ((n + sig - j) % BASE);
        }
        while (!a.back()) a.pop_back();
    }

    void set(const char *s) { set((string)s); }

    void clear() {
        a.clear();
        sig = false;
    }

    BigInt operator-() const {
        BigInt ans = *this;
        ans.sig ^= true;
        return ans;
    }

    template<typename T>
    operator T() const {
        T ans = 0;
        for (size_t i : a) {
            (ans *= MOD) += i;
        }
        return sig ? -ans : ans;
    }

    operator string() const {
        if (!*this) return "0";
        string ans;
        if (sig) ans = "-";
        for (size_t i = a.size() - 1; i + 1; i--) {
            string s = std::to_string(a[i]);
            if (i + 1 < a.size()) {
                ans += string(BASE - s.length(), '0');
            }
            ans += s;
        }
        return ans;
    }

    friend std::istream &operator>>(std::istream &in, BigInt &bigInt) {
        string s;
        in >> s;
        bigInt = s;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &bigInt) {
        return out << (string)bigInt;
    }

    operator bool() const { return !a.empty(); }

  private:

    std::vector<size_t> a;
    bool sig;
    static const size_t BASE = 8;
    static const size_t MOD = 1e8;
};

#endif




#include <iostream>
using std::cout;
using std::cin;

int main() {
    BigInt a, b, c;
    cin >> a;
    b = c = 12435235;
    cout << a << " " << b << " " << c;
    std::string s;
}
