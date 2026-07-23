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
    template<typename T> BigInt(const T &x) { set(x); }
    template<typename T> BigInt operator=(const T &x) { return set(x), *this; }
    void clear() { a.clear(), sig = false; }
    size_t operator[](int i) const { return a[i]; }
    size_t &operator[](int i) { return a[i]; }
    
    // Set BigInt with Other Types
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

    BigInt operator-() const {
        BigInt ans = *this;
        ans.sig ^= (bool)*this;
        return ans;
    }

    // Transfer to Other Types
    template<typename T>
    operator T() const {
        T ans = 0;
        for (size_t i : a) {
            (ans *= MOD) += i;
        }
        return sig ? -ans : ans;
    }

    operator bool() const { return !a.empty(); }

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

    // Input And Output
    friend std::istream &operator>>(std::istream &in, BigInt &bigInt) {
        string s;
        in >> s;
        bigInt = s;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &bigInt) {
        return out << (string)bigInt;
    }

    // BigInt Compare BigInt
    bool operator==(const BigInt &bigInt) const {
        return (a.empty() && bigInt.a.empty()) || 
            (a == bigInt.a && sig == bigInt.sig);
    }

    bool operator<(const BigInt &bigInt) const {
        if (!*this && !bigInt) return false;
        if (!*this) return !bigInt.sig;
        if (!bigInt) return sig;
        if (sig != bigInt.sig) return bigInt.sig < sig;
        if (a.size() != bigInt.a.size()) return sig ^ (a.size() < bigInt.a.size());
        for (size_t i = a.size() - 1; i + 1; i--) {
            if (a[i] != bigInt[i]) {
                return sig ^ (a[i] < bigInt[i]);
            }
        }
        return false;
    }

    bool operator!=(const BigInt &bigInt) const { return !(*this == bigInt); }
    bool operator> (const BigInt &bigInt) const { return bigInt < *this; }
    bool operator<=(const BigInt &bigInt) const { return !(bigInt < *this); }
    bool operator>=(const BigInt &bigInt) const { return !(*this < bigInt); }

    // BigInt Compare Other Types
    template<typename T> bool operator==(const T &x) const { return *this == (BigInt)x; }
    template<typename T> bool operator< (const T &x) const { return *this <  (BigInt)x; }
    template<typename T> bool operator!=(const T &x) const { return *this != (BigInt)x; }
    template<typename T> bool operator> (const T &x) const { return *this >  (BigInt)x; }
    template<typename T> bool operator<=(const T &x) const { return *this <= (BigInt)x; }
    template<typename T> bool operator>=(const T &x) const { return *this >= (BigInt)x; }

    // Other Types Compare BigInt
    template<typename T> friend bool operator==(const T &x, const BigInt &bigInt) { return (BigInt)x == bigInt; }
    template<typename T> friend bool operator< (const T &x, const BigInt &bigInt) { return (BigInt)x <  bigInt; }
    template<typename T> friend bool operator!=(const T &x, const BigInt &bigInt) { return (BigInt)x != bigInt; }
    template<typename T> friend bool operator> (const T &x, const BigInt &bigInt) { return (BigInt)x >  bigInt; }
    template<typename T> friend bool operator<=(const T &x, const BigInt &bigInt) { return (BigInt)x <= bigInt; }
    template<typename T> friend bool operator>=(const T &x, const BigInt &bigInt) { return (BigInt)x >= bigInt; }
    

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
    BigInt a, b;
    cin >> a >> b;
    cout << (a < b);
}
