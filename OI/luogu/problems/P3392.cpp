#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::istream;
using std::min;

template<typename T> istream &operator>>(istream &in, vector<T> &x) { for (T &i : x) in >> i; return in; }

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    cin >> a;
    vector<int> W(n), B(n), R(n);
    for (int i = 0; i < n; i++) {
        for (char c : a[i]) {
            if (c == 'W') W[i]++;
            else if (c == 'B') B[i]++;
            else R[i]++;
        }
    }
    int ans = n * m;
    for (int w = 0; w < n - 2; w++) {
        for (int b = w + 1; b < n - 1; b++) {
            int y = 0;
            for (int i = 0; i <= w; i++) {
                y += m - W[i];
            }
            for (int i = w + 1; i <= b; i++) {
                y += m - B[i];
            }
            for (int i = b + 1; i < n; i++) {
                y += m - R[i];
            }
            ans = min(ans, y);
        }
    }
    cout << ans;
}