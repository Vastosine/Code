#include <vector>
using namespace std;

const int M = 1e9 + 7;

struct Matric {
    using ll = long long;
    using vll = vector<ll>;
    Matric(int n, int m) : n(n), m(m), a(n, vll(m)) {}
    Matric(int n = 0) : Matric(n, n) {}

    static Matric identity(int n) {
        Matric a(n);
        for (int i = 0; i < n; i++) a[i][i] = 1;
        return a;
    }

    bool canMulti(const Matric &matric) const { return m == matric.n; }

    Matric operator*(const Matric &matric) const {
        if (!canMulti(matric)) return {};
        Matric ans(n, matric.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < matric.m; j++) {
                __int128 res = 0;
                for (int k = 0; k < m; k++) {
                    res += a[i][k] * matric[k][j];
                }
                ans[i][j] = res % M;
            }
        }
        return ans;
    }

    Matric &operator*=(const Matric &matric) { return *this = *this * matric; };

    Matric operator^(unsigned long long N) const {
        if (n != m) return {};
        Matric cur = *this, res = identity(n);
        while (N) {
            if (N & 1) res *= cur;      // 这里看的是幂 N 的最低位，不是阶数 n
            cur *= cur;
            N /= 2;
        }
        return res;
    }

    Matric &operator^=(unsigned long long N) { return *this = *this ^ N; }

    vll &operator[](int id) { return a[id]; }
    const vll &operator[](int id) const { return a[id]; }
  private:
    int n, m;
    vector<vll> a;
};