#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const int N = 5e3, M = 1e9 + 7;

long long f(long long x) { return x * (x - 1) / 2 % M; }

int main() {
    int n;
    cin >> n;
    vector<long long> a(N + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }
    long long ans = 0;
    for (int i = 2; i <= N; i++) {
        if (a[i] >= 2) {
            long long y = 0;
            y += ((i + 1) % 2) * f(a[i / 2]);
            for (int j = 1; j * 2 < i; j++) {
                (y += a[j] * a[i - j]) %= M;
            }
            (ans += y * f(a[i])) %= M;
        }
    }
    cout << ans;
}