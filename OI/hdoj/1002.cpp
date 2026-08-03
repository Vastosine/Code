#include <iostream>

using std::cin;
using std::cout;

#ifndef __BIG_INT__
#define __BIG_INT__

#include <iostream>
#include <vector>

class BigInt {
  public:
    typedef unsigned long long size_t;
    typedef std::string string;
    BigInt() : sig(false) {}
    template<typename T> BigInt(const T &x) { set(x); }
    template<typename T> BigInt operator=(const T &x) { return set(x), *this; }
    void clear() { a.clear(), sig = false; }
    size_t operator[](size_t i) const { return a[i]; }
    size_t &operator[](size_t i) { return a[i]; }
    signed sign() const { return *this ? sig ? -1 : 1 : 0; }
    BigInt abs() const { return BigInt(a); }
    
    // Set BigInt with Other Types
    template<typename T>
    void set(const T &X) {
        T x = X;
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
        clear_zero();
    }

    void set(const char *s) { set((string)s); }

    BigInt operator-() const {
        BigInt ans = *this;
        ans.sig ^= (bool)*this;
        return ans;
    }

    // Transfer to Other Types
    // template<typename T>
    operator long long() const {
        long long ans = (size_t)*this;
        if (sig) ans = -ans;
        return ans;
    }

    operator size_t() const {
        size_t ans = 0;
        for (size_t i : a) {
            (ans *= MOD) += i;
        }
        return ans;
    }

    operator bool() const { return !a.empty(); }

    operator string() const {
        if (!*this) return "0";
        string ans;
        if (sig) ans = "-";
        for (size_t i = size() - 1; i + 1; i--) {
            string s = std::to_string(a[i]);
            if (i + 1 < size()) {
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
            (a == bigInt.a && sign() == bigInt.sign());
    }

    bool operator<(const BigInt &bigInt) const {
        if (sign() != bigInt.sign()) return sign() < bigInt.sign();
        if (size() != bigInt.size()) return sig ^ (size() < bigInt.size());
        for (size_t i = size() - 1; i + 1; i--) {
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
    
    // operator (BigInt op BigInt)
    BigInt operator+(const BigInt &bigInt) const {
        if (sign() != bigInt.sign()) {
            if (!bigInt) return *this;
            if (!*this) return bigInt;
            return *this - (-bigInt);
        }
        BigInt ans;
        ans.sig = sig;
        size_t n = size(), m = bigInt.size(), add = 0;
        for (size_t i = 0; i < n || i < m; i++) {
            if (i < n) add += a[i];
            if (i < m) add += bigInt[i];
            ans.a.push_back(add % MOD);
            add = add / MOD;
        }
        return ans;
    }

    BigInt operator-(const BigInt &bigInt) const { 
        if (sign() != bigInt.sign()) {
            if (!bigInt) return *this;
            if (!*this) return -bigInt;
            return *this + (-bigInt);
        }
        if ((*this < bigInt) ^ sig) return -(bigInt - *this);
        BigInt ans = *this;
        size_t n = size(), m = bigInt.size();
        for (size_t i = 0; i < n; i++) {
            if (i < m) ans[i] -= bigInt[i];
            if (ans[i] + MOD < MOD) ans[i] += MOD, ans[i + 1]--;
            else if (i >= m) break;
        }
        ans.clear_zero();
        return ans;
    }

    BigInt operator*(const BigInt &bigInt) const {
        if (!*this || !bigInt) return BigInt();
        BigInt ans;
        ans.sig = sig ^ bigInt.sig;
        size_t add = 0, n = size(), m = bigInt.size();
        for (size_t i = 0; ; i++) {
            if (!add && i >= n + m - 1) break;
            size_t ADD = add / MOD, j = 0;
            add %= MOD;
            if (i >= m) j = i - m + 1;
            for (; j <= i && j < n; j++) {
                add += a[j] * bigInt[i - j];
                ADD += add / MOD;
                add %= MOD; 
            }
            ans.a.push_back(add);
            add = ADD;
        }
        return ans;
    }

    BigInt operator/(const BigInt &bigInt) const {
        if (!bigInt) throw std::exception();
        if (!*this) return BigInt();
        BigInt x = this->abs(), y = bigInt.abs(), ans;
        ans.sig = sig ^ bigInt.sig;
        if (x < y) return BigInt();
        if (y.back() >= 10) {
            size_t t = 10;
            while (y.back() * t < MOD) t *= 10;
            x *= t;
            y *= t;
        }
        size_t e = x.size() - y.size(), top = y.back();
        BigInt z = y.switch_to(e);
        ans.a.assign(e + 1, 0);
        while (true) {
            while (x > y && x.size() > z.size()) {
                x -= z * (MOD / (top + 1));
                ans[e] += MOD / (top + 1);
            }
            if (x < y) break;
            size_t add = 0;
            while (x.size() == z.size() && (add = x.back() / (top + 1))) {
                x -= z * add;
                ans[e] += add;
            }
            while (x >= z) {
                x -= z;
                ans[e]++;
            }
            z = z.switch_to(-1);
            e--;
        }
        ans.clear_zero();
        return ans;
    }

    BigInt operator%(const BigInt &bigInt) const {
        return *this - *this / bigInt * bigInt; 
    }

    // operator (BigInt op Other Types, Other Types op BigInt, BigInt op= Types)
    template<typename T> BigInt operator+(const T &x) const { return *this + (BigInt)x; }
    template<typename T> friend BigInt operator+(const T &x, const BigInt &bigInt) { return BigInt(x) + bigInt; }
    template<typename T> BigInt &operator+=(const T &x) { return *this = *this + x; }

    template<typename T> BigInt operator-(const T &x) const { return *this - (BigInt)x; }
    template<typename T> friend BigInt operator-(const T &x, const BigInt &bigInt) { return BigInt(x) - bigInt; }
    template<typename T> BigInt &operator-=(const T &x) { return *this = *this - x; }

    template<typename T> 
    BigInt operator*(const T &X) const {
        T x = X;
        if (x > 1e9 || x < -1e9) return *this * (BigInt) x;
        BigInt ans;
        if (x < 0) ans.sig = true, x = -x;
        size_t n = size(), add = 0;
        for (size_t i = 0; i < n || add; i++) {
            if (i < n) add += x * a[i];
            ans.a.push_back(add % MOD);
            add /= MOD;
        }
        return ans;
    }
    template<typename T> friend BigInt operator*(const T &x, const BigInt &bigInt) { return bigInt * x; }
    template<typename T> BigInt &operator*=(const T &x) { return *this = *this * x; }

    template<typename T>
    BigInt operator/(const T &X) const {
        if (!X) throw std::exception();
        if (!*this) return BigInt();
        if (X > 1e9 || X < -1e9) return *this / (BigInt)X;
        size_t add = 0;
        BigInt ans;
        ans.sig = sig ^ (X < 0);
        ans.a.assign(size(), 0);
        T x = X;
        if (x < 0) x = -x;
        for (size_t i = size() - 1; i + 1; i--) {
            (add *= MOD) += a[i];
            ans[i] += add / x;
            add %= x;
        }
        ans.clear_zero();
        return ans;
    }
    template<typename T> friend BigInt operator/(const T &x, const BigInt &bigInt) { return (BigInt)x / bigInt; }
    template<typename T> BigInt &operator/=(const T &x) { return *this = *this / x; }

    template<typename T> BigInt operator%(const T &x) const { return *this - *this / x * x; }
    template<typename T> friend BigInt operator%(const T &x, const BigInt &bigInt) { return new BigInt(x) % bigInt; }
    template<typename T> BigInt &operator%=(const T &x) { return *this = *this % x; }

  private:

    std::vector<size_t> a;
    bool sig;
    static const size_t BASE = 8;
    static const size_t MOD = 1e8;

    void clear_zero() { while (!a.empty() && !a.back()) a.pop_back(); }
    size_t size() const { return a.size(); }
    size_t &back() { return a.back(); }
    size_t back() const { return a.back(); }
    BigInt(const std::vector<size_t> &a, bool sig = false) : a(a), sig(sig) {}
    BigInt switch_to(long long x) const {
        if (!x) return *this;
        long long n = size();
        if (x + n < 0) return BigInt();
        BigInt ans;
        ans.sig = sig;
        ans.a.assign(x + n, 0);
        for (size_t i = x < 0 ? -x : 0; i < n; i++) {
            ans[i + x] = a[i];
        }
        return ans;
    }
};

#endif

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":\n";
        BigInt a, b;
        cin >> a >> b;
        cout << a << " + " << b << " = " << a + b << "\n\n";
    }
}