#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::istream;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n);
    cin >> a;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.') t++;
            else t = 0;
            if (t >= k) ans++;
        }
    }
    for (int j = 0; j < m; j++) {
        int t = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][j] == '.') t++;
            else t = 0;
            if (t >= k) ans++;
        }
    }
    cout << ans;
}