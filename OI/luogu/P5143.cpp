#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::istream;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) cin >> i; return in; }

double f(double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(3));
    cin >> a;
    std::sort(a.begin(), a.end(), 
        [] (const vector<int> &x, const vector<int> &y) {
            return x.back() < y.back();
        }
    );
    double ans = 0;
    for (int i = 1; i < n; i++) {
        ans += f(a[i][0] - a[i - 1][0], a[i][1] - a[i - 1][1], a[i][2] - a[i - 1][2]);
    }
    cout << std::fixed << std::setprecision(3) << ans;
}