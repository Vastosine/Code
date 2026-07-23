#ifndef __BIG_INT__
#define __BIG_INT__

#include <vector>
#include <string>


class BigInt {
  public:
    typedef unsigned long long size_t;
    
    template<typename T> BigInt(T x) { set(x); }
    BigInt(const std::string &s) { set(s); }
    
    template<typename T> BigInt operator=(T x) { 
        set(x); 
        return *this;
    }
    BigInt operator=(const std::string &s) { 
        set(s); 
        return *this;
    }
    
    template<typename T>
    void set(T x) {
        clear();
        if (x < 0) x = -x, sig = true;
        while (x) a.push_back(x % MOD), x /= MOD;
    }

    void set(const std::string &s) {
        clear();
        if (s[0] == '-') sig = true;
        for (size_t i = s.length() - 1, j = 0; i >= 0 && s[i] != '-'; i--, j++) {
            if (!(j % BASE)) a.push_back(s[i] - '0');
            else (*(a.end() - 1) *= MOD) += s[i] - '0';
        }
    }

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

    operator std::string() const {
        std::string ans;
        if (sig) ans = "-";
        for (size_t i = a.size() - 1; i + 1; i--) {
            std::string s = std::to_string(a[i]);
            if (i + 1 < a.size()) {
                ans += std::string(BASE - s.length(), '0');
            }
            ans += s;
        }
        return ans;
    }

    

  private:

    std::vector<size_t> a;
    bool sig;
    static const size_t BASE = 8;
    static const size_t MOD = 1e8;
};

#endif




#include <iostream>
using std::cout;

int main() {
    BigInt a = 123456789123;
    // a = 1;


    cout << (std::string)a;
}
