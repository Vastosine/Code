#include <vector>
using namespace std;

const int M = 1e9 + 7;

class Matrix {
  public:
    using ll = long long;
    using vll = vector<ll>;
    Matrix(int n, int m) : n(n), m(m), a(n, vll(m)) {}
    Matrix(int n = 0) : Matrix(n, n) {}

    static Matrix identity(int n) {
        Matrix a(n);
        for (int i = 0; i < n; i++) a[i][i] = 1;
        return a;
    }

    bool canMulti(const Matrix &matrix) const { return m == matrix.n; }

    Matrix operator*(const Matrix &matrix) const {
        if (!canMulti(matrix)) return {};
        Matrix ans(n, matrix.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < matrix.m; j++) {
                __int128 res = 0;
                for (int k = 0; k < m; k++) {
                    res += a[i][k] * matrix[k][j];
                }
                ans[i][j] = res % M;
            }
        }
        return ans;
    }

    Matrix &operator*=(const Matrix &matrix) { return *this = *this * matrix; };

    Matrix operator^(unsigned long long N) const {
        if (n != m) return {};
        Matrix cur = *this, res = identity(n);
        while (N) {
            if (N & 1) res *= cur;
            cur *= cur;
            N /= 2;
        }
        return res;
    }

    Matrix &operator^=(unsigned long long N) { return *this = *this ^ N; }

    vll &operator[](int id) { return a[id]; }
    const vll &operator[](int id) const { return a[id]; }
  private:
    int n, m;
    vector<vll> a;
};